#include "ArrayList.h"
#include "Board.h"
#include "Piece.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

Board *createBoard(void){
    Board *board = malloc(sizeof(Board));
    board->board = calloc(64, sizeof(Piece*));
    board->display = calloc(17 * 34, sizeof(char));
    board->state = FREE;
    return board;
}
//[1,2,3]
//[4,5,6]
//[7,8,9]

//Sets position on board to specified piece
//piece can be null to 'clear' a position on the board
//Side effect: sets piece's pos to specified new pos
int boardSet(Board *board, Piece *piece, const int y, const int x){
    int pos = getPos(y, x);
    assert(piece==NULL || board->board[pos]==NULL);
    if(piece != NULL) piece->pos = pos;
    board->board[pos] = piece;
    return 0;
}

void boardInit(Board *board){
    //rhbqkpRHBQKP
    for(int ind=0; ind<8; ind++){
        boardSet(board, createPiece('p'), 1, ind);
        boardSet(board, createPiece('P'), 6, ind);
    }
    char *pieceStr = "rhbqkbhrRHBQKBHR";
    ArrayList *pieces = createPieces(pieceStr);
    pieces->print(pieces);
    for(int ind=0; ind<16; ind++){
        if(ind<8) boardSet(board, pieces->arr[ind], 0, ind);
        else  boardSet(board, pieces->arr[ind], 7, ind-8);
    }
    destroyArrayList(pieces, 0);
    pieces = NULL;
}
//converts y,x into pos index for a one dim board array
int getPos(int y, int x){
    assert(y<=7 && y>=0 && x<=7 && x>=0);
    return y*8 + x;
}
int getDisplayPos(int y, int x){
    assert(y<=7 && y>=0 && x<=7 && x>=0);
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
//Init Display (redraw board squares)
//Draw Move stuct (to show what happend)
//Draw pieces
void updateDisplay(Board *board){
    initDisplay(board);
    //Draw Move
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

