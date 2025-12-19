#ifndef MOVETREE_H
#define MOVETREE_H
#include "ArrayList.h"
#include "Board.h"
#include "Piece.h"

typedef struct MoveNode MoveNode;
typedef struct MoveTree MoveTree;

struct MoveNode {
    int moveDepth;
    Board *board;
    ArrayList *children;
    ArrayList *before;
    ArrayList *after;
}

struct MoveTree {
    MoveNode *head;
}

MoveNode *createMoveNode(void);
MoveNode *createMoveTree(void);
