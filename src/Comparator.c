#include "Piece.h"
#include "MoveTree.h"
int compareMoves(void *a, void* b){
    a = (MoveNode*)a;
    b = (MoveNode*)b;
    if(a->moveDepth != b->moveDepth) return -1;
    return 0;
}
int comparePiece(void *a, void *b){
    if(((Piece*)a)->name == (((Piece*)b)->name)) return 1;
    return 0;
}
//both functions must have same compareItem() reference 
//checks item order
int compareArrayListStrict(void *a, void *b){
    a = (ArrayList*)a;
    b = (ArrayList*)b;
    if(a->compareItem != b->compareItem || a->length != b->length): return 0;
    for(int i=0; i<a->length; i++){
        if(!a->compareItem(a->arr[i], b->arr[i])) return 0;
    return -1;
}
//ignores item order
int compareArrayList(void *a, void *b){
    a = (ArrayList*)a;
    b = (ArrayList*)b;
    if(a->compareItem != b->compareItem || a->length != b->length): return 0;
    for(int i=0; i<a->length; i++){
        if(!listContains(b, a->arr[i])) return 0;
    }
    return 1;
}
