#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "MoveTree.h"
#include "ArrayList.h"
#include "Piece.h"

MoveNode *createMoveNode(){
    MoveNode *node = calloc(1, sizeof(MoveNode));
    node->pieceList = calloc(4, sizeof(Piece*));
    return node;
}
void printMoveNode(MoveNode *node){
    assert(node != NULL);
    printf("[%s]",node->name);
}
//side effect creates children array if one does not exist
int addNode(MoveNode *node, MoveNode *add){
    if(!node->children) node->children = createArrayList();
    listAdd(node->children, add);
    return node->children->length-1;
}
//asserts children is empty/null
void destroyNode(MoveNode *node){
    assert(!node->children || node->children->length == 0);
    destroyArrayList(node->children, 0);
    node->prev = NULL;
    free(node->pieceList);
    node->pieceList = NULL;
    free(node);
}
void addNodePiece(MoveNode *node, Piece *piece, int before, int after, int ind){
    assert(ind<3 && !node->pieceList[ind]);
    node->pieceList[ind] = piece;
    node->before[ind] = before;
    node->after[ind] = after;
}
void genMoveName(MoveNode *node){
    assert(node->pieceList[0]);
    node->name[0] = (char) 97 + (node->before[1]&7);
    node->name[1] = (char) 56 - (node->before[0]>>3);
    node->name[2] = (char) 97 + (node->after[1]&7);
    node->name[3] = (char) 56 - (node->after[0]>>3);
    node->name[4] = '\0';
}
void printMoveArray(ArrayList *list){
    printf("[");
    for(int ind=0; ind<list->length; ind++){
        const char* name = ((MoveNode*)list->arr[ind])->name;
        int i = 0;
        printf("'");
        while(name[i]) printf("%c", name[i++]);
        printf("'");
        if(ind<list->length-1) printf(",");
    }
    printf("]\n");
}
    

