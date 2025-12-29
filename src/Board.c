#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "ArrayList.h"
#include "MoveTree.h"
#include "Board.h"
#include "Piece.h"

static const char pieceStr[] = {
    'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r', 
    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'
};

Board *createBoard(void){
    Board *board = malloc(sizeof(Board));
    board->board = calloc(64, sizeof(Piece*));
    board->pieceList = malloc(sizeof(ArrayList));
    board->display = calloc(17 * 34, sizeof(char));
    board->pieceList = NULL;
    board->gameStart = createMoveNode();
    board->currMove = board->gameStart;
    board->moveTotal = 0;
    char *name = "game";
    strcpy(board->gameStart->name, name);
    board->state = FREE;
    return board;
}
//[1,2,3]
//[4,5,6]
//[7,8,9]
int getTurn(Board *board){
    return (board->moveTotal&1) == 0 ? -1 : 1;
}

//Sets position on board to specified piece
//piece can be null to 'clear' a position on the board
//Side effect: sets piece's pos to specified new pos
//also sets cleared pieces to -1
int boardSetTwoD(Board *board, Piece *piece, const int y, const int x){
    boardSet(board, piece, getPos(y, x));
}
int boardSet(Board *board, Piece *piece, int pos){
    //if(piece) printf("piece: %c, dest: %d\n", piece->name, pos);
    assert(piece==NULL || board->board[pos]==NULL);
    if(piece != NULL) piece->pos = pos; 
    else{
        assert(board->board[pos]);
        board->board[pos]->pos = -1;
    }
    board->board[pos] = piece;
    return 0;
}

void boardInit(Board *board){
    board->pieceList = createPieces(pieceStr);
    for(int ind=0; ind<32; ind++){
        if(ind<16) boardSet(board, board->pieceList->arr[ind], ind);
        else  boardSet(board, board->pieceList->arr[ind], ind+32);
    }
}
//converts y,x into pos index for a one dim board array
int getPos(int y, int x){
    assert(validTwoD(y,x));
    return y*8 + x;
}
int getInputPos(char *input){
    int y = '8'-input[1], x = input[0] - 'a';
    return getPos(y, x);
}

int validOneD(int pos){
    return pos>=0 && pos<64 ? 1 : 0;
}

int validTwoD(int y, int x){
    return (y<=7 && y>=0 && x<=7 && x>=0) ? 1 : 0;
}
//adds a move from an input string like "a7a5"
int addInputMove(Board *board, char *input){
    int pos = getInputPos(input);
    int dest = getInputPos(input+2);
    Piece *piece = board->board[pos];
    if(!piece || getColor(piece) == getTurn(board)) return -1;
    if(!canMovePiece(piece, dest, board)) return -1;
    MoveNode *move = genMovePiece(piece, dest, board);
    if(isCompromising(move, board)) return -1;
    return addNode(board->currMove, move);
}
//validates if a player's move puts them in check
//assumes we can move forward on given move
int isCompromising(MoveNode *move, Board *board){
    assert(move);
    moveForward(board, addNode(board->currMove, move));
    int ret = isInCheck(getColor(move->pieceList[0]), board);
    printf("ret %d\n", ret);
    moveBackward(board);
    removeChild(board->currMove, board->currMove->children->length-1);
    return ret;
}

//currMove must have children nodes
int moveForward(Board *board, int ind){
    assert(board->currMove);
    assert(board->gameStart);
    if(!board->currMove->children) return 0;
    assert(ind < board->currMove->children->length);
    board->currMove = board->currMove->children->arr[ind];
    int i = 0;
    const int *before = board->currMove->before;
    const int *after = board->currMove->after;
    while(board->currMove->pieceList[i]){
        //printf("pieceList[i]: %c\n", board->currMove->pieceList[i]->name);
        if(before[i] != -1) boardSet(board, NULL, before[i]);
        i++;
    }
    i = 0;
    while(board->currMove->pieceList[i]){
        if(after[i] != -1) boardSet(board, board->currMove->pieceList[i], after[i]);
        i++;
    }
    board->currMove->pieceList[0]->moveCount++;
    board->moveTotal++;
    return 1;
}
int moveBackward(Board *board){
    assert(board->currMove);
    assert(board->gameStart);
    if(board->currMove == board->gameStart) return 0;
    assert(board->currMove->prev);
    int i = 0;
    const int *before = board->currMove->before;
    const int *after = board->currMove->after;
    while(board->currMove->pieceList[i]){
        if(after[i] != -1) boardSet(board, NULL, after[i]);
        i++;
    }
    i = 0;
    while(board->currMove->pieceList[i]){
        if(before[i] != -1) boardSet(board, board->currMove->pieceList[i], before[i]);
        i++;
    }
    board->currMove->pieceList[0]->moveCount--;
    board->moveTotal--;
    board->currMove = board->currMove->prev;
    return 1;
}

int getDisplayPos(int y, int x){
    assert(validTwoD(y,x));
    return y*2*34+34 + x*4+1;
}
    
void setDisplay(Board *board, int y, int x, char a, char b, char c){
    int pos = getDisplayPos(y, x);
    board->display[pos] = a; 
    board->display[pos+1] = b; 
    board->display[pos+2] = c; 
}
void initDisplay(Board *board){
    for(int y = 0; y < 17; y++){
        board->display[(y+1)*34 - 1] = '\n';
        for(int x = 0; x < 33; x++){
            if(y%2 == 0 && ((y==0||(y==16 && x%4!=2) || (y>0&&y<16&&x>0&&x<32))))board->display[y*34+x]='-';
            else if(y%2==1 && x==0) board->display[y*34+x] = (char) ('8' - y/2);
            else if(y==16 && x%4==2) board->display[y*34+x] = (char) ('a' + x/4);
            else if(x%4==0) board->display[y*34+x] = '|';
            else if((((y/2)%2 + x/4))%2 == 0) board->display[y*34+x] = ':';
            else board->display[y*34+x] = ' ';
        }
    }
    board->display[34*17] = '\0';
}
void drawMove(Board *board, MoveNode* move){
    if(!move->pieceList[0]) return;
    int pos=move->before[0], dest=move->after[0], i=1;
    while(dest == -1) dest = move->after[i++];
    assert(dest>-1 && dest<64);
    int xPos = pos&7, yPos = pos>>3;
    setDisplay(board, yPos, xPos, 'o', 'o', 'o');
    int xDest = dest&7, yDest = dest>>3;
    setDisplay(board, yDest, xDest, '[', ' ', ']');
    if(move->pieceList[0]->name=='h' || move->pieceList[0]->name=='H') return;
    int x = (xDest-xPos), y = (yDest-yPos);
    if(x) x/=abs(xDest-xPos);
    if(y) y/=abs(yDest-yPos);
    while(xPos+x != xDest || yPos+y != yDest) setDisplay(board, yPos+=y, xPos+=x, 'o', 'o', 'o');
}


    
//Init Display (redraw board squares)
//Draw Move stuct (to show what happend)
//Draw pieces
void updateDisplay(Board *board, int displayMove){
    initDisplay(board);
    if(displayMove) drawMove(board, board->currMove);
    for(int y=0; y<8; y++){
        for(int x=0; x<8; x++){
            Piece *piece = board->board[getPos(y,x)];
            if(piece != NULL){
                int pos = getDisplayPos(y,x);
                char a = board->display[pos];
                char b = board->display[pos+2];
                setDisplay(board, y, x, a, piece->name, b);
            }
        }
    }
}
void printDisplay(Board *board){
    printf("%s\n", board->display);
}

