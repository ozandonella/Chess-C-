#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct{
    void **arr;
    unsigned length;
    unsigned capacity;
} ArrayList;

typedef int (*Comparator)(const void *a, const void *b);

ArrayList *createArrayList(void);
int listAdd(ArrayList *list, void *item);
int listContains(ArrayList *list, void *item, Comparator cmp);

#endif
