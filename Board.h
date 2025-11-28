#ifndef PIECE_H
#define PIECE_H

#include "Piece.h"
typedef struct {
   Piece **board;
   int gameState;
} Board;

Board *createBoard(void);
void printBoard(const *Board);
#endif
    
