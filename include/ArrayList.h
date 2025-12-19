#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "Comparator"

typedef struct ArrayList ArrayList;
typedef void (*PrintFunc)(ArrayList *list);

struct ArrayList{
    void **arr;
    Comparator *compareItem
    PrintFunc print;
    unsigned length;
    unsigned capacity;
};

ArrayList *createArrayList(void);
void destroyArrayList(ArrayList *list, int destroyContents);
int listAdd(ArrayList *list, void *item);
int listContains(ArrayList *list, void *item);

#endif
