#include "Piece.h"
#include "MoveTree.h"
#include "ArrayList.h"
/*int compareMoves(void *a, void* b){
    MoveNode *nodeA = (MoveNode*)a;
    MoveNode *nodeB = (MoveNode*)b;
    if(nodeA->moveDepth != nodeB->moveDepth) return -1;
    return 0;
}*/
int comparePiece(void *a, void *b){
    if(((Piece*)a)->name == (((Piece*)b)->name)) return 1;
    return 0;
}
//both functions must have same compareItem() reference 
//checks item order
int compareArrayListStrict(void *a, void *b){
    ArrayList *listA = (ArrayList*)a;
    ArrayList *listB = (ArrayList*)b;
    if(listA->compareItem != listB->compareItem || listA->length != listB->length) return 0;
    for(int i=0; i<listA->length; i++){
        if(!listA->compareItem(listA->arr[i], listB->arr[i])) return 0;
    }
    return -1;
}
//ignores item order
int compareArrayList(void *a, void *b){
    ArrayList *listA = (ArrayList*)a;
    ArrayList *listB = (ArrayList*)b;
    if(listA->compareItem != listB->compareItem || listA->length != listB->length) return 0;
    for(int i=0; i<listA->length; i++){
        if(!listContains(b, listA->arr[i])) return 0;
    }
    return 1;
}
