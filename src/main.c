#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Board.h"
#include "Piece.h"
#include "MoveTree.h"
int moveStringSize = 0;
char *moveString;
void addMove();
void printMoves();
int validateMove(char *m);
int main(){
    Board *board = createBoard();
    boardInit(board);
    updateDisplay(board);
    printDisplay(board);
    Piece *piece = board->board[8];
    printf("name:%c pos:%d\n",piece->name, piece->pos);
    for(int i=0; i<64; i++){
       CanMove canMove = piece->pieceFunction->canMove;
       GenMove genMove = piece->pieceFunction->genMove;
       if(canMove(piece, i, board)){
           MoveNode *move = genMove(piece, i, board);
           genMoveName(move);
           printf("piece: %s\n", move->pieceList[0]);
           printf("name: %c, before: %d, after: %d\n", move->pieceList[0]->name, move->before[0], move->after[0]);
           addNode(board->currMove, move);
           printMoveArray(board->currMove->children);
       }
    }

    return 0;
}
void addMove(){
    puts("enter a move [letter][number][letter][number]");
    char *input = malloc(5);
    while(true){
        scanf("%4s",input);
        if(validateMove(input)) break;
        else puts("invalid move");
    }
    int size = strlen(moveString);
    moveString = realloc(moveString, size + 5); 
    int ind = 0;
    while(moveString[size++] = input[ind++]);
    free(input);
}
int validateMove(char *m){
    return (strlen(m) != 4 ||
    m[0] > 72 || m[0] < 65 ||
    m[2] > 72 || m[2] < 65 ||
    m[1] > 56 || m[1] < 49 ||
    m[3] > 56 || m[3] < 49); 
}
void printMoves(){
    char *ptr = moveString;
    int len = strlen(moveString);
    for(int x = 0; x < len; x+=4){
        printf("%c%c%c%c\n", ptr[x+0], ptr[x+1], ptr[x+2], ptr[x+3]);
    }
}




