#include "ArrayList.h"
#include "Piece.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

ArrayList *createArrayList(void){
    ArrayList *list = malloc(sizeof(ArrayList));
    list->arr = calloc(10, sizeof(void*));
    list->print = NULL;
    list->compareItem = NULL;
    list->length = 0;
    list->capacity = 10;
    return list;
}
void destroyArrayList(ArrayList *list, int destroyContents){
    if(!list) return;
    if(destroyContents){
        for(int ind=0; ind<list->length; ind++){
            free(list->arr[ind]);
            list->arr[ind] = NULL;
        }
    }
    free(list->arr);
    list->arr = NULL;
    list->print = NULL;
    list->compareItem = NULL;
    free(list);
}


int listAdd(ArrayList *list, void *item){
    if(list->length == list->capacity){
        list->arr = realloc(list->arr, sizeof(void*) * (list->capacity+10));
        list->capacity += 10;
    }
    list->arr[list->length] = item;
    return list->length++;
}
int listContains(ArrayList *list, void *item){
    for(int ind=0; ind<list->length; ind++){
        if(list->compareItem(list->arr[ind], item)) return ind;
    }
    return -1;
}


