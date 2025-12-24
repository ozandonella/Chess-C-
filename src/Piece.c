#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Board.h"
#include "Piece.h"
#include "ArrayList.h"
#include "Comparator.h"
#include "MoveTree.h"

static const char *pieceNames = "rhbqkpRHBQKP";
static const MovePattern movePatterns[6] =  {
    {0, 8, {{-1, 0}, {-2, 0}, {-1, 1}, {1, 1}, {1, 0}, {2, 0}, {1,-1}, {1, -1}}}, //Pawn
    {1, 4, {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}}, //Rook
    {0, 8, {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}}}, //Horse
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
int getColor(Piece *piece){
    assert(piece!=NULL);
    return piece->name<'a' ? 1 : -1;
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
//magic pieceList numbers, black king: 4, white king: 28.
int isInCheck(int color, Board* board){
    Piece *king = color == -1 ? board->pieceList->arr[4] : board->pieceList->arr[28];
    return hasAttackers(king->pos, -getColor(king), board);
}

//finds any pieces of specified color that are attacking pos
//special cases for non attacking moves associated with pawn and king
int hasAttackers(int pos, int color, Board* board){
    for(int i=0; i<board->pieceList->length; i++){
        Piece *piece = board->pieceList->arr[i];
        if(color == getColor(piece) && piece->pos != -1){
            int patInd = matchPattern(piece, pos);
            if(patInd == -1) return 0;
            const int *pattern = piece->pieceFunction->movePattern->dists[patInd];
            if(canReach(piece, pattern, pos, board)){
                if(piece->name == 'p'|| piece->name == 'P')
                    return getColor(piece)*pattern[0] < 0 && pattern[1] != 0;
                if(piece->name != 'k' && piece->name != 'K')
                    return abs(pattern[1] == 1);
                return 1;
            }
        }
    }
    return 0;
}
/*static const MovePattern movePatterns[6] =  {
    {0, 8, {{-1, 0}, {-2, 0}, {-1, 1}, {1, 1}, {1, 0}, {2, 0}, {1,-1}, {1, -1}}}, //Pawn
    {1, 4, {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}}, //Rook
    {0, 8, {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}}}, //Horse
    {1, 4, {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}}}, //Bishop
    {1, 8, {{-1,0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}}, //Queen
    {0, 10, {{-1,0}, {-1, 1}, {0, 1}, {0, 2}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {0,-2}, {-1, -1}}} //King
};*/
//returns ind in pattern array of given piece that can be used to reach dest or -1 if none exist
int matchPattern(Piece *piece, int dest){
    const MovePattern *pattern = piece->pieceFunction->movePattern;
//    printf("validating pattern");
    int xPos = piece->pos&7, yPos = piece->pos>>3;
    int xDist = (dest&7) - (xPos), yDist = (dest>>3) - (yPos);
    if(xDist == 0 && yDist == 0) return -1;
    //printf("yPos: %d, xPos: %d, xDist: %d, yDist: %d\n", yPos, xPos, xDist, yDist);
    for(int i=0; i<pattern->moveCount; i++){
        if(validTwoD(yPos + pattern->dists[i][0], xPos + pattern->dists[i][1])){
            //printf("pattern: [%d, %d]\n",pattern->dists[i][0], pattern->dists[i][1]);
            if(pattern->dists[i][0] == yDist && pattern->dists[i][1] == xDist)  return i;
            else if(pattern->doesRep){
                int squares = abs(xDist) + abs(yDist);
                //printf("squares: %d\n", squares);
                if(pattern->dists[i][0] != 0 && pattern->dists[i][1] != 0) squares = squares>>1;
                if(pattern->dists[i][0]*squares == yDist && pattern->dists[i][1]*squares == xDist) return i;
            }
        }
    }
    return -1;
}
//checks for blocking pieces during a pattern, assumes dest is a valid pos and pattern goes to dest
int canReach(Piece *piece, const int *pattern, int dest, Board* board){
    int temp = piece->pos;
    Piece *blocker = NULL;
    while(temp != dest){
        temp += pattern[0]*8 + pattern[1];
        blocker = board->board[temp];
        if(blocker!=NULL) break;
    }
    return blocker==NULL || (temp == dest && getColor(blocker) != getColor(piece));
}

int xDist(int start, int dest){
    assert(validOneD(start) && validOneD(dest));
    return dest%8 - start%8;
}

int yDist(int start, int dest){
    assert(validOneD(start) && validOneD(dest));
    return dest/8 - start/8;
}
int checkCastle(Piece *king, const int *pattern, Board *board){
    return 1;
}
//assumes pattern is on a valid diagonal also checks enpass
int checkPawnCapture(Piece *pawn, const int *pattern, Board *board){
    Piece *destPiece = board->board[pawn->pos + pattern[0]*8 + pattern[1]];
    if(destPiece) return getColor(destPiece) != getColor(pawn);
    Piece *capture = board->currMove->pieceList[0];
    return (capture->name == 'p' || capture->name == 'P') &&
        (pawn->pos + pattern[1] == board->currMove->after[0]);
}

int canMovePawn(Piece *piece, int dest, Board *board){
    assert(piece->name == 'p' || piece->name == 'P');
    int pInd = matchPattern(piece, dest);
    if(pInd == -1) return 0;
    const int *pattern = piece->pieceFunction->movePattern->dists[pInd];
    if(getColor(piece)*pattern[0] > 0) return 0;
    if(abs(pattern[0]) > 1 && (piece->moveCount || board->board[piece->pos + pattern[0]*4])) return 0;
    //at this point pawn is moving to a legal square in the right direction without jumping over anything
    if(pattern[1] != 0 && !checkPawnCapture(piece, pattern, board)) return 0;
    if(pattern[1] == 0 && board->board[piece->pos + pattern[0]*8]) return 0;
    //generate move and find out if in check
    return 1;
}
int canMoveRook(Piece *piece, int dest, Board *board){
    assert(piece->name == 'r' || piece->name == 'R');
    int pInd = matchPattern(piece, dest);
    if(pInd == -1) return 0;
    const int *pattern = piece->pieceFunction->movePattern->dists[pInd];
    if(!canReach(piece, pattern, dest, board)) return 0; 
    //generate move and find out if in check
    return 1;
}
int canMoveHorse(Piece *piece, int dest, Board *board){
    assert(piece->name == 'h' || piece->name == 'H');
    int pInd = matchPattern(piece, dest);
    if(pInd == -1) return 0;
    const int *pattern = piece->pieceFunction->movePattern->dists[pInd];
    if(!canReach(piece, pattern, dest, board)) return 0; 
    return 1;
}
int canMoveBishop(Piece *piece, int dest, Board *board){
    assert(piece->name == 'b' || piece->name == 'B');
    int pInd = matchPattern(piece, dest);
    if(pInd == -1) return 0;
    const int *pattern = piece->pieceFunction->movePattern->dists[pInd];
    if(!canReach(piece, pattern, dest, board)) return 0; 
    return 1;
}
int canMoveQueen(Piece *piece, int dest, Board *board){
    assert(piece->name == 'q' || piece->name == 'Q');
    int pInd = matchPattern(piece, dest);
    if(pInd == -1) return 0;
    const int *pattern = piece->pieceFunction->movePattern->dists[pInd];
    if(!canReach(piece, pattern, dest, board)) return 0; 
    return 1;
}
int canMoveKing(Piece *piece, int dest, Board *board){
    assert(piece->name == 'k' || piece->name == 'K');
    int pInd = matchPattern(piece, dest);
    if(pInd == -1) return 0;
    const int *pattern = piece->pieceFunction->movePattern->dists[pInd];
    if(abs(pattern[1]) > 1 && (piece->moveCount ||
        board->board[piece->pos + pattern[1]>>1] ||
        board->board[piece->pos + pattern[1]])) return 0;
    else if(!canReach(piece, pattern, dest, board)) return 0; 
    return 1;
}

//ALL GEN MOVES ASSUME CAN MOVE HAS BEEN ASSERTED
//pawn gen will not handle premotion that will be done at some point later
MoveNode *genMovePawn(Piece *piece, int dest, Board *board){
    MoveNode *move = createMoveNode();
    addNodePiece(move, piece, piece->pos, dest, 0);
    printf("piece after function: %c\n", move->pieceList[0]->name);
    int x = dest&7 - piece->pos&7;
    if(x){
        Piece *capture = board->board[dest] ? board->board[dest] : board->board[piece->pos+x];
        addNodePiece(move, capture, capture->pos, -1, 1);
    }
    return move;
}
MoveNode *genMoveRook(Piece *piece, int dest, Board *board){
    assert(piece->name == 'r' || piece->name == 'R');
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
