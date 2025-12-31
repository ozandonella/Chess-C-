#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Board.h"
#include "Piece.h"
#include "ArrayList.h"
#include "Comparator.h"
#include "MoveNode.h"

static const char *pieceNames = "rhbqkpRHBQKP";
static const MovePattern movePatterns[6] =  {
    {0, 8, {{-1, 0}, {-2, 0}, {-1, 1}, {1, 1}, {1, 0}, {2, 0}, {1,-1}, {-1, -1}}}, //Pawn
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
    piece->moveCount = 0;
    piece->movePattern = getPiecePattern(piece->name); 
    piece->promotions = (name == 'p' || name =='P') ? calloc(3, sizeof(Piece*)) : NULL;
    return piece;
}
int getColor(Piece *piece){
    assert(piece!=NULL);
    return piece->name<'a' ? 1 : -1;
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
const MovePattern *getPiecePattern(char name){
    if(name > 'R') name = (char) name-32;
    switch(name){
        case 'P': return &movePatterns[0];
        case 'R': return &movePatterns[1];
        case 'H': return &movePatterns[2];
        case 'B': return &movePatterns[3];
        case 'Q': return &movePatterns[4];
        case 'K': return &movePatterns[5];
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
            if(patInd == -1) continue;
            const int *pattern = piece->movePattern->dists[patInd];
            if(canReach(piece, pattern, pos, board)){
                if(piece->name == 'p'|| piece->name == 'P'){
                    if(getColor(piece)*pattern[0] < 0 && pattern[1] != 0) return 1;
                }
                else if(piece->name == 'k' || piece->name == 'K'){
                    if(abs(pattern[1])==1) return 1;
                }
                else return 1;
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
    const MovePattern *pattern = piece->movePattern;
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
    return (dest&7) - (start&7);
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
    Piece *capture = board->board[pawn->pos + pattern[0]*8 + pattern[1]];
    if(capture) return getColor(capture) != getColor(pawn);
    capture = board->board[pawn->pos + pattern[1]];
    return capture && (capture->name == 'p' || capture->name == 'P') &&
        (getColor(capture) != getColor(pawn)) &&
        (capture == board->currMove->pieceList[0]) &&
        (capture->moveCount == 1);
}

//does not validate if move avoids check
int canMovePiece(Piece *piece, int dest, Board *board){
    assert(piece);
    if(!validOneD(dest)) return 0;
    int pInd = matchPattern(piece, dest);
    if(pInd == -1) return 0;
    const int *pattern = piece->movePattern->dists[pInd];
    if(piece->name == 'p' || piece->name == 'P') return canMovePawn(piece, pattern, dest, board);
    if(piece->name == 'k' || piece->name == 'K') return canMoveKing(piece, pattern, dest, board);
    if(!canReach(piece, pattern, dest, board)) return 0; 
    return 1;
}
//assumes pattern is patternMatched and canReach
int canMovePawn(Piece *piece, const int *pattern, int dest, Board *board){
    if(getColor(piece)*pattern[0] > 0) return 0;
    if(abs(pattern[0]) > 1 && (piece->moveCount || board->board[piece->pos + pattern[0]*4])) return 0;

    //at this point pawn is moving to a legal square in the right direction without jumping over anything
    if(pattern[1] != 0 && !checkPawnCapture(piece, pattern, board)) return 0;
    if(pattern[1] == 0 && board->board[piece->pos + pattern[0]*8]) return 0;
    return 1;
}
int canMoveKing(Piece *piece, const int *pattern, int dest, Board *board){
    assert(piece->name == 'k' || piece->name == 'K');
    if(abs(pattern[1]) > 1){
        Piece *rook = board->board[dest + (pattern[1]<0 ? -2 : +1)];
        if(piece->moveCount || !rook || rook->moveCount) return 0;
        int inc = pattern[1]>>1, tempPos = piece->pos, tempDest = dest;
        if(hasAttackers(piece->pos, -getColor(piece), board) || board->board[rook->pos-inc]) return 0;
        while(tempPos != tempDest){
            tempPos+=inc;
            if(board->board[tempPos] || hasAttackers(tempPos, -getColor(piece), board)) return 0;
            //printf("rook: %c, pos: %d tempPos: %d\n", rook->name, rook->pos, tempPos);
        }
    }
    //printf("name: %c, x: %d, y: %d, pos: %d, dest: %d\n", piece->name, pattern[1], pattern[0], piece->pos, dest);
    else if(!canReach(piece, pattern, dest, board)) return 0; 
    return 1;
}
//returns index in move pieceList where the promoted piece was added
//adds promotion to board pieceList
//assumes move is a valid promotion move where pieceList[0] == pawn and after[0] lies on promotion rank
int promotePawnMove(MoveNode* move, char name, Board* board){
    assert(name == 'h' || name == 'H' || name == 'q' || name == 'Q');
    assert(move->pieceList[0]->promotions);
    Piece *promo = NULL;
    int ind = (name == 'h' || name == 'H') ? 0 : 1;
    if(!move->pieceList[0]->promotions[ind]){
        move->pieceList[0]->promotions[ind] = createPiece(name);
        listAdd(board->pieceList, promo);
    }
    promo = move->pieceList[0]->promotions[ind];
    ind = 0;
    while(move->pieceList[++ind]); //find open index
    addNodePiece(move, promo, -1, move->after[0], ind);
    move->after[0] = -1; //pawn removed from board
    //printf("pieceList[0]: %c %d %d\n", move->pieceList[0]->name, move->before[0], move->after[0]);
    //printf("pieceList[1]: %c %d %d\n", move->pieceList[1]->name, move->before[1], move->after[1]);
    //printf("pieceList[ind]: %c %d %d\n", move->pieceList[ind]->name, move->before[ind], move->after[ind]);
    assert(ind);
    return ind;
}
int checkForPromotion(MoveNode* move){
    //printf("piece: %c before: %d after: %d\n", move->pieceList[0]->name, move->before[0], move->after[0]);
    if(move->pieceList[0]->name != 'p' && move->pieceList[0]->name != 'P') return 0;
    return (move->after>=0 && move->after[0] < 8) || move->after[0] > 55;
}
//ALL GEN MOVES ASSUME CAN MOVE HAS BEEN ASSERTED
//pawn gen will not handle premotion that will be done at some later point
MoveNode *genMovePiece(Piece *piece, int dest, Board *board){
    MoveNode *move = createMoveNode();
    addNodePiece(move, piece, piece->pos, dest, 0);
    if(piece->name == 'p' || piece->name == 'P'){
        int x = (dest&7) - (piece->pos&7);
        if(x && !board->board[dest]) addNodePiece(move, board->board[piece->pos+x], piece->pos+x, -1, 1);
    }
    if(piece->name == 'k' || piece->name == 'K'){
        int x = (dest&7) - (piece->pos&7);
        if(abs(x)>1){
            Piece *rook = board->board[dest + (x<0 ? -2 : 1)];
            addNodePiece(move, rook, rook->pos, piece->pos + (x>>1), 1);
        }
    }
    if(board->board[dest]) addNodePiece(move, board->board[dest], dest, -1, 1);
    genMoveName(move);
    return move;
}

//generates all moves for piece (size of 30) and returns them
MoveNode **genAllPieceMoves(Piece *piece, Board *board){
    assert(piece->pos != -1);
    int ind = 0;
    MoveNode **moves = calloc(30, sizeof(MoveNode*)); 
    //Testing
    //for(int i=0; i<64; i++) if(canMovePiece(piece, i, board)) moves[ind++] = genMovePiece(piece, i, board);

    //Testing
    const MovePattern* movePattern = piece->movePattern;
    for(int i=0; i<movePattern->moveCount; i++){
        int destx=piece->pos&7, desty=piece->pos>>3;
        const int *dist = movePattern->dists[i];
        desty+=dist[0];
        destx+=dist[1];
        if(!validTwoD(desty, destx)) continue;
        int dest = getPos(desty, destx);
        if(canMovePiece(piece, dest, board)){
            moves[ind++] = genMovePiece(piece, dest, board);
            if(movePattern->doesRep){ 
                while(validTwoD(desty+=dist[0], destx+=dist[1])){
                    dest = getPos(desty, destx);
                    if(canMovePiece(piece, dest, board)) moves[ind++] = genMovePiece(piece, dest, board);
                }
            }
        }
    }
    //If generating pawn moves modify any existing promotion moves to queen and add horse
    if(piece->name == 'p' || piece->name == 'P'){
        for(int i=0; moves[i]; i++){
            if(checkForPromotion(moves[i])){
                MoveNode* currMove = moves[i];
                MoveNode *horsePromo = genMovePiece(piece, currMove->after[0], board);
                int color = getColor(piece);
                promotePawnMove(horsePromo, color == -1 ? 'H' : 'h', board);
                promotePawnMove(currMove, color == -1 ? 'Q' : 'q', board);
                moves[ind++] = horsePromo;
            }
        }
    }
    return moves;
}
