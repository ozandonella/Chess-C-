#ifndef PIECE_H
#define PIECE_H
#include "def.h"
struct MovePattern {
    int doesRep;
    int moveCount;
    const int dists[10][2];
};
struct PieceFunction {
    CanMove canMove;
    GenMove genMove;
    const MovePattern *movePattern;
};

struct Piece {
    PieceFunction *pieceFunction;
    Piece **promotions;
    int pos;
    char name;
    int moveCount;
}; 

PieceFunction *getPieceFunction(char name);
int canMovePawn(Piece *piece, int dest, Board *board);
int canMoveRook(Piece *piece, int dest, Board *board);
int canMoveHorse(Piece *piece, int dest, Board *board);
int canMoveBishop(Piece *piece, int dest, Board *board);
int canMoveQueen(Piece *piece, int dest, Board *board);
int canMoveKing(Piece *piece, int dest, Board *board);
MoveNode *genMovePawn(Piece *piece, int dest, Board *board);
MoveNode *genMoveRook(Piece *piece, int dest, Board *board);
MoveNode *genMoveHorse(Piece *piece, int dest, Board *board);
MoveNode *genMoveBishop(Piece *piece, int dest, Board *board);
MoveNode *genMoveQueen(Piece *piece, int dest, Board *board);
MoveNode *genMoveKing(Piece *piece, int dest, Board *board);
int promotePawnMove(MoveNode* move, char name, Board* board);
int checkForPromotion(MoveNode* pawnMove);
MoveNode **genAllMoves(Piece *piece, Board *board);
int matchPattern(Piece *piece, int dest);
int canReach(Piece *piece, const int *pattern, int dest, Board* board);
int hasAttackers(int pos, int color, Board* board);
int isInCheck(int color, Board* board);
int isWhite(Piece *piece);
void printPieceArray(ArrayList *list);
Piece *createPiece(char name);
ArrayList *createPieces(const char *names);
int isValidName(char name);
#endif
