#include <assert.h>
#include <stdio.h>
#include "MoveNode.h"
#include "ArrayList.h"
#include "Board.h"
//void saveLine

void generateDepth(Board *board, int depth){
    if(depth == 0) return;
    MoveNode **moves = genAllPlayerMoves(board, getTurn(board));
    int ind = 0;
    while(moves[ind]){
        addNode(board->currMove, moves[ind++]);
        moveForward(board, board->currMove->children->length-1);
        generateDepth(board, depth-1);
        moveBackward(board);
    }
}


