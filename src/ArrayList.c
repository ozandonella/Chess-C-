#include "ArrayList.h"
#include <assert.h>
#include <stdlib.h>

ArrayList *createArrayList(void){
    ArrayList *list = malloc(sizeof(ArrayList));
    list->arr = calloc(10, sizeof(void*));
    list->length = 0;
    list->capacity = 10;
    return list;
}
int listAdd(ArrayList *list, void *item){
    if(list->length == list->capacity){
        list->arr = realloc(list->arr, sizeof(void*)*10);
        list->capacity += 10;
    }
    list->arr[list->length] = item;
    return list->length++;
}
int listContains(ArrayList *list, void *item, Comparator cmp){
    for(int ind=0; ind<list->length; ind++){
        if(cmp(list->arr[ind], item)) return ind;
    }
    return -1;
}


