#include <assert.h>
#include <stdio.h>
#include "MoveNode.h"
#include "Bot.h"
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
//prints perftCounts for specified node's immediate children 
void perftDivide(MoveNode *move){
    assert(move->children);
    for(int i=0; i<move->children->length; i++){
        MoveNode* curr = (MoveNode *)move->children->arr[i];
        printf("%s: %d\n", curr->name, perftCount(curr));
    }
}

int perftCount(MoveNode *node){
    assert(node);
    int total = 0;
    if(!node->children) return 1;
    for(int i=0; i<node->children->length; i++) total += perftCount((MoveNode *)node->children->arr[i]);
    return total;
}
