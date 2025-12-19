#ifndef COMPARATOR_H
#define COMPARATOR_H

typedef int (*Comparator)(const void *a, const void *b);
int comparePiece(void *a, void *b);
