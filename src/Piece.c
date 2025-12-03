#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Piece.h"
#include "ArrayList.h"

static const char *pieceNames = "rhbqkpRHBQKP";
Piece *createPiece(char name){
    Piece *piece = malloc(sizeof(int) + sizeof(char));
    piece->name = name;
    piece->pos = -1;
    return piece;
}

ArrayList *createPieces(char *names){
    ArrayList *list = createArrayList();
    int len = strlen(names);
    int ind = 0;
    while(names[ind]){
        if(isValidName(names[ind])){
            listAdd(list, createPiece(names[ind]));
        }
        ind++;
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
