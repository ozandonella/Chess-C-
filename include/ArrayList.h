#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct ArrayList ArrayList;
typedef int (*Comparator)(const void *a, const void *b);
typedef void (*PrintFunc)(ArrayList *list);

struct ArrayList{
    void **arr;
    PrintFunc print;
    unsigned length;
    unsigned capacity;
};

ArrayList *createArrayList(void);
void destroyArrayList(ArrayList *list, int destroyContents);
int listAdd(ArrayList *list, void *item);
int listContains(ArrayList *list, void *item, Comparator cmp);

#endif
