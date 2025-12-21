#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Board.h"
#include "Piece.h"
#include "ArrayList.h"
#include "Comparator.h"

static const char *pieceNames = "rhbqkpRHBQKP";
static const MovePattern movePatterns[6] =  {
    {0, 8, {{-1, 0}, {-2, 0}, {-1, 1}, {1, 1}, {1, 0}, {2, 0}, {1,-1}, {1, -1}}}, //Pawn
    {1, 4, {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}}, //Rook
    {0, 8, {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, 2}}}, //Horse
    {1, 4, {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}}}, //Bishop
    {1, 8, {{-1,0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}}, //Queen
    {0, 10, {{-1,0}, {-1, 1}, {0, 1}, {0, 2}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {0,-2}, {-1, -1}}} //King
};
Piece *createPiece(char name){
    Piece *piece = malloc(sizeof(Piece));
    piece->name = name;
    piece->pos = -1;
    piece->pieceFunction = getPieceFunction(piece->name); 
    return piece;
}
int isWhite(Piece *piece){
    return piece->name<'a' ? 1 : 0;
}
ArrayList *createPieces(const char *names){
    ArrayList *list = createArrayList();
    list->compareItem = comparePiece;
    list->print = printPieceArray;
    for(int ind=0; names[ind]; ind++){
        if(isValidName(names[ind])){
            listAdd(list, createPiece(names[ind]));
        }
    }
    return list;
}
void printPieceArray(ArrayList *list){
    printf("[");
    for(int ind=0; ind<list->length; ind++){
        //CONSIDER MAKING PRINT OBJECT UTIL
        printf("'%c'", ((Piece*)list->arr[ind])->name);
        if(ind<list->length-1) printf(",");
    }
    printf("]\n");
}
int isValidName(char name){
    int ind = 0;
    while(pieceNames[ind]) if(pieceNames[ind++] == name) return 1;
    return 0;
}
PieceFunction *getPieceFunction(char name){
    if(name > 'R') name = (char) name-32;
    PieceFunction *pieceFunction = malloc(sizeof(PieceFunction));
    switch(name){
        case 'P':
            pieceFunction->genMove = genMovePawn;
            pieceFunction->canMove = canMovePawn;
            pieceFunction->movePattern = &movePatterns[0];
            return pieceFunction;
        case 'R': 
            pieceFunction->genMove = genMoveRook;
            pieceFunction->canMove = canMoveRook;
            pieceFunction->movePattern = &movePatterns[1];
            return pieceFunction;
        case 'H': 
            pieceFunction->genMove = genMoveHorse;
            pieceFunction->canMove = canMoveHorse;
            pieceFunction->movePattern = &movePatterns[2];
            return pieceFunction;
        case 'B':
            pieceFunction->genMove = genMoveBishop;
            pieceFunction->canMove = canMoveBishop;
            pieceFunction->movePattern = &movePatterns[3];
            return pieceFunction;
        case 'Q':
            pieceFunction->genMove = genMoveQueen;
            pieceFunction->canMove = canMoveQueen;
            pieceFunction->movePattern = &movePatterns[4];
            return pieceFunction;
        case 'K': 
            pieceFunction->genMove = genMoveKing;
            pieceFunction->canMove = canMoveKing;
            pieceFunction->movePattern = &movePatterns[5];
            return pieceFunction;
    }
    return NULL;
}
/*static const MovePattern movePatterns[6] =  {
    {0, 8, {-8, -16, -7, 9, 8, 16, 7, -9}}, //Pawn
    {1, 4, {-8, 1, 8, -1}}, //Rook
    {0, 8, {-15, -6, 10, 17, 15, 6, -10, -17}}, //Horse
    {1, 4, {-7, 9, 7, -9}}, //Bishop
    {1, 8, {-8, -7, 1, 9, 8, 7, -1, -9}}, //Queen
    {0, 10, {-8, -7, 1, 2, 9, 8, 7, -1, -2, -9}} //King
};*/
int validPattern(Piece *piece, int dest){
    const MovePattern *pattern = piece->pieceFunction->movePattern;
    for(int i=0; i<pattern->moveCount; i++){
        int x = (dest&7) - (piece->pos&7), y = (dest>>7) - (piece->pos>>7);
        if(pattern->dists[i][0] == x && pattern->dists[0][1] == y) return 1;
        else if(pattern->doesRep){
        }


    }
return 1;
}

int xDist(int start, int dest){
    assert(validOneD(start) && validOneD(dest));
    return dest%8 - start%8;
}

int yDist(int start, int dest){
    assert(validOneD(start) && validOneD(dest));
    return dest/8 - start/8;
}

int canMovePawn(Piece *piece, int dest, Board *board){
    assert(piece->name == 'p' || piece->name == 'P');
    printf("moving pawn\n");
    
    return 1;
}
int canMoveRook(Piece *piece, int dest, Board *board){
    assert(piece->name == 'r' || piece->name == 'R');
    printf("moving rook\n");
    return 1;
}
int canMoveHorse(Piece *piece, int dest, Board *board){
    assert(piece->name == 'h' || piece->name == 'H');
    printf("moving horse\n");
    return 1;
}
int canMoveBishop(Piece *piece, int dest, Board *board){
    assert(piece->name == 'b' || piece->name == 'B');
    printf("moving bishop\n");
    return 1;
}
int canMoveQueen(Piece *piece, int dest, Board *board){
    assert(piece->name == 'q' || piece->name == 'Q');
    printf("moving Queen\n");
    return 1;
}
int canMoveKing(Piece *piece, int dest, Board *board){
    assert(piece->name == 'k' || piece->name == 'K');
    printf("moving King\n");
    return 1;
}

//ALL GEN MOVES ASSUME CAN MOVE HAS BEEN ASSERTED
MoveNode *genMovePawn(Piece *piece, int dest, Board *board){
    printf("moving pawn\n");
    return NULL;
}
MoveNode *genMoveRook(Piece *piece, int dest, Board *board){
    printf("moving rook\n");
    return NULL;
}
MoveNode *genMoveHorse(Piece *piece, int dest, Board *board){
    printf("moving horse\n");
    return NULL;
}
MoveNode *genMoveBishop(Piece *piece, int dest, Board *board){
    printf("moving bishop\n");
    return NULL;
}
MoveNode *genMoveQueen(Piece *piece, int dest, Board *board){
    printf("moving Queen\n");
    return NULL;
}
MoveNode *genMoveKing(Piece *piece, int dest, Board *board){
    printf("moving King\n");
    return NULL;
}
