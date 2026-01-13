#include <assert.h>
#include <stdio.h>
#include "MoveNode.h"
#include "Bot.h"
#include "ArrayList.h"
#include "Board.h"
#include "Piece.h"
const int pawnMap[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    9, 9, 9, 9, 9, 9, 9, 9,
    6, 6, 6, 6, 6, 6, 6, 6,
    4, 4, 4, 4, 4, 4, 4, 4, 
    2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
const int horseMap[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 3, 3, 3, 3, 2, 1, 
    1, 2, 3, 3, 3, 3, 2, 1,
    0, 1, 2, 3, 3, 2, 1, 0,
    0, 1, 2, 2, 2, 2, 1, 0,
    0, 1, 1, 2, 2, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
};
const int mopUp[] = {
    9, 5, 4, 3, 3, 4, 5, 9,
    5, 4, 3, 2, 2, 3, 4, 5,
    4, 3, 2, 1, 1, 2, 3, 4,
    3, 2, 1, 0, 0, 1, 2, 3,
    3, 2, 1, 0, 0, 1, 2, 3,
    4, 3, 2, 1, 1, 2, 3, 4,
    5, 4, 3, 2, 2, 3, 4, 5,
    9, 5, 4, 3, 3, 4, 5, 9,
};
//void saveLine

//MoveNode *findBestMove(Board* board){

int evaluateBoard(Board *board){
    int value=0, whiteCount=0, blackCount=0;
    if(board->state == STALE) return value;
    if(board->state == CHECKMATE) return 1000 * getTurn(board);
    for(int i=0; i<board->pieceList->length; i++){
        Piece *piece = (Piece *)board->pieceList->arr[i];
        if(piece->pos == -1) continue;
        if(getColor(piece) == -1){
            if(piece->name == 'p') value -= pawnMap[63 - piece->pos];
            if(piece->name == 'h') value -= horseMap[63 - piece->pos];
            blackCount++;
        }
        else{
            if(piece->name == 'P') value += pawnMap[piece->pos];
            if(piece->name == 'H') value += horseMap[piece->pos];
            whiteCount++;
        }
        value += piece->value;
    }
    int bk = ((Piece *)board->pieceList->arr[4])->pos, wk = ((Piece *)board->pieceList->arr[28])->pos;
    if(getTurn(board) == -1){
        value += (mopUp[bk]/blackCount);
        if(board->state == CHECK) value += 3;
    }
    else{
        value -= mopUp[wk];
        if(board->state == CHECK) value -= 3;
    }
    return value;
}
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
