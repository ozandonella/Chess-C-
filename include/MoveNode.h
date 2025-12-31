#ifndef MOVENODE_H
#define MOVENODE_H
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

MoveNode *createMoveNode(void);
MoveNode *createMoveTree(void);
void printMoveTree(MoveNode *node);
void printMoveRec(MoveNode *node, int depth, int needsSpace);
void printMoveNode(MoveNode *node);
int addNode(MoveNode *node, MoveNode *add);
int removeChild(MoveNode *parent, int childInd);
void addNodePiece(MoveNode *node, Piece *piece, int before, int after, int ind);
void destroyNode(MoveNode *node); //asserts children is empty/null
void destroyTree(MoveNode *node);
void genMoveName(MoveNode *node);
void printMoveArray(ArrayList *list);

#endif
