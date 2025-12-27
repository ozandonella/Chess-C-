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
    const MovePattern *movePattern;
    Piece **promotions;
    int pos;
    char name;
    int moveCount;
}; 

const MovePattern *getPiecePattern(char name);
int canMovePawn(Piece *piece, const int *pattern, int dest, Board *board);
int canMoveKing(Piece *piece, const int *pattern, int dest, Board *board);
int canMovePiece(Piece *piece, int dest, Board *board);
MoveNode *genMovePiece(Piece *piece, int dest, Board *board);
MoveNode *genMovePawn(Piece *piece, int dest, Board *board);
MoveNode *genMoveKing(Piece *piece, int dest, Board *board);
int promotePawnMove(MoveNode* move, char name, Board* board);
int checkForPromotion(MoveNode* move);
int checkPawnCapture(Piece *pawn, const int *pattern, Board *board);
MoveNode **genAllMoves(Piece *piece, Board *board);
int matchPattern(Piece *piece, int dest);
int canReach(Piece *piece, const int *pattern, int dest, Board* board);
int hasAttackers(int pos, int color, Board* board);
int isInCheck(int color, Board* board);
int getColor(Piece *piece);
void printPieceArray(ArrayList *list);
Piece *createPiece(char name);
ArrayList *createPieces(const char *names);
int isValidName(char name);
#endif
