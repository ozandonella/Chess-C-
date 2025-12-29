#ifndef BOARD_H
#define BOARD_H
#include "def.h"

struct Board {
   Piece **board;
   ArrayList *pieceList;
   MoveNode *gameStart;
   MoveNode *currMove;
   int moveTotal;
   char *display;
   GameState state;
};

Board *createBoard(void);
int getTurn(Board *board);
int isCompromising(MoveNode *move, Board *board);
int addInputMove(Board *board, char *input);
int moveForward(Board *board, int ind);
int moveBackward(Board *board);
int boardSetTwoD(Board *board, Piece *piece, const int x, const int y);
int boardSet(Board *board, Piece *piece, int pos);
void boardInit(Board *board);
void boardPrint(Board *board);
int getDisplayPos(int y, int x);
int getPos(int y, int x);
int getInputPos(char *input);
int validTwoD(int y, int x);
int validOneD(int pos);
void setDisplay(Board *board, int y, int x, char a, char b, char c);
void updateDisplay(Board *board, int displayMove);
void initDisplay(Board *board);
void printDisplay(Board *board);
void drawMove(Board *board, MoveNode* move);
#endif
    
