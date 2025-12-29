#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "def.h"

struct ArrayList{
    void **arr;
    Comparator compareItem;
    PrintFunc print;
    unsigned length;
    unsigned capacity;
};

ArrayList *createArrayList(void);
void destroyArrayList(ArrayList *list, int destroyContents);
int listAdd(ArrayList *list, void *item);
void *listRemove(ArrayList *list, int ind);
int listContains(ArrayList *list, void *item);

#endif
