#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Piece.h"
#include "ArrayList.h"

static const char *pieceNames = "rhbqkpRHBQKP";
void printPieceArray(ArrayList *list){
    printf("[");
    for(int ind=0; ind<list->length; ind++){
        printf("'%c'", ((Piece*)list->arr[ind])->name);
        if(ind<list->length-1) printf(",");
    }
    printf("]\n");
}
Piece *createPiece(char name){
    Piece *piece = malloc(sizeof(Piece));
    piece->name = name;
    piece->pos = -1;
    return piece;
}
ArrayList *createPieces(char *names){
    ArrayList *list = createArrayList();
    list->print = printPieceArray;
    for(int ind=0; names[ind]; ind++){
        if(isValidName(names[ind])){
            listAdd(list, createPiece(names[ind]));
        }
    }
    return list;
}

int isValidName(char name){
    int ind = 0;
    while(pieceNames[ind]) if(pieceNames[ind++] == name) return 1;
    return 0;
}
int comparePiece(void *a, void *b){
    if(((Piece*)a)->name == (((Piece*)b)->name)) return 1;
    return 0;
}
