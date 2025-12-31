#ifndef BOT_H
#define BOT_H
#include "def.h"
void generateDepth(Board *board, int depth);
void perftDivide(MoveNode *move);
int perftCount(MoveNode *node);
#endif
