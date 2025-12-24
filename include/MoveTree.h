#ifndef MOVETREE_H
#define MOVETREE_H
#include "def.h"

struct MoveNode {
    MoveNode *prev;
    ArrayList *children;
    Piece **pieceList;
    char name[5];
    //At most three pieces must be tracked over a single move (case where a pawn promotes and captures)
    int before[3];
    int after[3];
};

struct MoveTree {
    MoveNode *head;
};

MoveNode *createMoveNode(void);
MoveNode *createMoveTree(void);
void printMoveNode(MoveNode *node);
int addNode(MoveNode *node, MoveNode *add);
void addNodePiece(MoveNode *node, Piece *piece, int before, int after, int ind);
void destroyNode(MoveNode *node); //asserts children is empty/null
void destroyTree(MoveNode *node);
void genMoveName(MoveNode *node);
void printMoveArray(ArrayList *list);

#endif
