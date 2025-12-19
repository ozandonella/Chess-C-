#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Piece.h"
#include "ArrayList.h"
#include "Comparator.h"

static const char *pieceNames = "rhbqkpRHBQKP";

Piece *createPiece(char name){
    Piece *piece = malloc(sizeof(Piece));
    piece->name = name;
    piece->pos = -1;
    piece->canMove = getMoveFunction(piece->name); 
    return piece;
}
int isWhite(Piece *piece){
    return piece->name<'a' ? 1 : 0;
}
ArrayList *createPieces(char *names){
    ArrayList *list = createArrayList();
    list->compareItem = comparePiece;
    list->print = printPieceArray;
    for(int ind=0; names[ind]; ind++){
        if(isValidName(names[ind])){
            listAdd(list, createPiece(names[ind]));
        }
    }
    return list;
}
void printPieceArray(ArrayList *list){
    printf("[");
    for(int ind=0; ind<list->length; ind++){
        //CONSIDER MAKING PRINT OBJECT UTIL
        printf("'%c'", ((Piece*)list->arr[ind])->name);
        if(ind<list->length-1) printf(",");
    }
    printf("]\n");
}
int isValidName(char name){
    int ind = 0;
    while(pieceNames[ind]) if(pieceNames[ind++] == name) return 1;
    return 0;
}
CanMove getMoveFunction(char name){
    if(name > 'R') name = (char) name-32;
    switch(name){
        case 'P': return canMovePawn;
        case 'R': return canMoveRook;
        case 'H': return canMoveHorse;
        case 'B': return canMoveBishop;
        case 'Q': return canMoveQueen;
        case 'K': return canMoveKing;
    }
    return NULL;
}
int canMovePawn(Piece *piece, int dest, Board *board){
    assert(piece->name == 'p' || piece->name == 'P');
    printf("moving pawn\n");
    return 1;
}
int canMoveRook(Piece *piece, int dest, Board *board){
    assert(piece->name == 'r' || piece->name == 'R');
    printf("moving rook\n");
    return 1;
}
int canMoveHorse(Piece *piece, int dest, Board *board){
    assert(piece->name == 'h' || piece->name == 'H');
    printf("moving horse\n");
    return 1;
}
int canMoveBishop(Piece *piece, int dest, Board *board){
    assert(piece->name == 'b' || piece->name == 'B');
    printf("moving bishop\n");
    return 1;
}
int canMoveQueen(Piece *piece, int dest, Board *board){
    assert(piece->name == 'q' || piece->name == 'Q');
    printf("moving Queen\n");
    return 1;
}
int canMoveKing(Piece *piece, int dest, Board *board){
    assert(piece->name == 'k' || piece->name == 'K');
    printf("moving King\n");
    return 1;
}
