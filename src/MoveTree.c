#include <stdlib.h>
#include "MoveTree.h"
#include "ArrayList.h"

struct MoveNode {
    MoveNode *prev;
    ArrayList *children;
    Piece **movers;
    //At most three pieces must be tracked over a single move (case where a pawn promotes and captures)
    int before[3];
    int after[3];
};
MoveNode *createMoveNode(void){
    MoveNode *node = calloc(1, sizeof(MoveNode));
    node->children = createArrayList();
    node->movers = calloc(4, sizeof(Piece*));
}
