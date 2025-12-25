#ifndef DEF_H
#define DEF_H
typedef struct Game Game;
typedef struct Board Board;
typedef enum {FREE, CHECK, CHECKMATE, STALE} GameState;
typedef struct ArrayList ArrayList;
typedef int (*Comparator)(void *a, void *b);
typedef struct Piece Piece;
typedef struct MoveTree MoveTree;
typedef struct MoveNode MoveNode;
typedef struct PieceFunction PieceFunction;
typedef struct MovePattern MovePattern;
typedef int (*CanMove)(Piece *piece, int dest, Board *board);
typedef MoveNode *(*GenMove)(Piece *piece, int dest, Board *board);
typedef void (*PrintFunc)(ArrayList *list);
#endif
