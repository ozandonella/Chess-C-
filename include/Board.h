#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
typedef enum {FREE, CHECK, CHECKMATE, STALE} GameState;

typedef struct Piece Piece;

typedef struct Board {
   Piece **board;
   char *display;
   GameState state;
} Board;

Board *createBoard(void);
int boardSet(Board *board, Piece *piece, const int x, const int y);
void boardInit(Board *board);
void boardPrint(Board *board);
int getDisplayPos(int y, int x);
int getPos(int y, int x);
void setDisplay(Board *board, int y, int x, char a, char b, char c);
void updateDisplay(Board *board);
void initDisplay(Board *board);
void printDisplay(Board *board);
#endif
    
