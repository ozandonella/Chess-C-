#ifndef PIECE_H
#define PIECE_H
#include "ArrayList.h"

typedef struct {
    int pos;
    char name;
} Piece;

static const char *pieceNames;

void printPieceArray(ArrayList *list);
Piece *createPiece(char name);
ArrayList *createPieces(char *names);
int isValidName(char name);
int comparePiece(void *a, void *b);
#endif
