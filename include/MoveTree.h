#ifndef MOVETREE_H
#define MOVETREE_H
#include "def.h"

typedef struct MoveNode MoveNode;
typedef struct MoveTree MoveTree;
typedef struct Piece Piece;

struct MoveNode {
    MoveNode *prev;
    ArrayList *children;
    Piece **movers;
    //At most three pieces must be tracked over a single move (case where a pawn promotes and captures)
    int before[3];
    int after[3];
};

struct MoveTree {
    MoveNode *head;
};

int addMoveNode(MoveNode *move, MoveNode *next);
MoveNode *createMoveNode(void);
MoveNode *createMoveTree(void);

#endif
