#ifndef PIECE_H
#define PIECE_H
#include "ArrayList.h"
#include "Board.h"

typedef struct Board Board;
typedef struct Piece Piece;
typedef int (*CanMove)(Piece *piece, int dest, Board *board);

struct Piece {
    CanMove canMove;
    int pos;
    char name;
    int moveCount;
};

CanMove getMoveFunction(char name);
int canMovePawn(Piece *piece, int dest, Board *board);
int canMoveRook(Piece *piece, int dest, Board *board);
int canMoveHorse(Piece *piece, int dest, Board *board);
int canMoveBishop(Piece *piece, int dest, Board *board);
int canMoveQueen(Piece *piece, int dest, Board *board);
int canMoveKing(Piece *piece, int dest, Board *board);
int isWhite(Piece *piece);
void printPieceArray(ArrayList *list);
Piece *createPiece(char name);
ArrayList *createPieces(char *names);
int isValidName(char name);
int comparePiece(void *a, void *b);
#endif
