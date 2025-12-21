#ifndef BOARD_H
#define BOARD_H
#include "def.h"

struct Board {
   Piece **board;
   ArrayList *pieceList;
   MoveTree *gameTree;
   char *display;
   GameState state;
};

Board *createBoard(void);
int moveForward(void);
int moveBackward(void);
int boardSet(Board *board, Piece *piece, const int x, const int y);
void boardInit(Board *board);
void boardPrint(Board *board);
int getDisplayPos(int y, int x);
int getPos(int y, int x);
int validTwoD(int y, int x);
int validOneD(int pos);
void setDisplay(Board *board, int y, int x, char a, char b, char c);
void updateDisplay(Board *board);
void initDisplay(Board *board);
void printDisplay(Board *board);
#endif
    
