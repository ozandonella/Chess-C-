#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "Piece.h"
#include "MoveTree.h"
#include "ArrayList.h"
const char *inputString = "INPUT LIST\n"
"move: [letter][number][letter][number]\n"
"forward: [F], back: [B], end: [end]\n";
const char *promoteString = "CHOOSE PROMOTION\n";
const char *cantMoveForwardString = "CANT MOVE FORWARD\n";
const char *cantMoveBackString = "CANT MOVE BACK\n";
const char *chooseForwardString = "CHOOSE PATH FORWARD\n";
void addMove();
void playGame(Board *board);
char *getInput();
char *getPromoInput();
int getForwardInput();
int validateMove(char *m);
void saveGame(Board *board, char *name);
Board *playSaved(char *textFile);

int main(){
    char *fileName = "./saved/test.txt";
    //saveGame(playGame(), fileName);
    playGame(playSaved("./saved/promotion.txt"));
    //Board *board = createBoard();
    //boardInit(board);
    //playGame(board);
    return 1;
}
void saveGame(Board *board, char *name){
    assert(board->gameStart);
    FILE *file = fopen(name, "w");
    MoveNode *curr = board->gameStart;
    while(curr->children && curr->children->length){
        curr = curr->children->arr[0];
        fprintf(file, "%s\n", curr->name); 
    }
    fclose(file);
}
Board *playSaved(char *textFile){
    FILE *file = fopen(textFile, "r");
    char move[6];
    Board *board = createBoard();
    boardInit(board);
    while(fgets(move, sizeof(move), file)){
        moveForward(board, addInputMove(board, move));
        updateDisplay(board, 1);
        printDisplay(board);
        printf("%s\n", move); 
    }
    fclose(file);
    return board;
}
void playGame(Board *board){
    updateDisplay(board, 0);
    printDisplay(board);
    printf(inputString); 
    while(1){
        char *input = getInput();
        if(*input == 'F'){
            MoveNode *move = board->currMove;
            if(!move->children || !move->children->length){
                printf(cantMoveForwardString);
                continue;
            }
            else if(move->children->length == 1) moveForward(board, 0);
            else moveForward(board, getForwardInput());
        }
        else if(*input == 'B'){
            if(!board->currMove->prev){
                printf(cantMoveBackString); 
                continue;
            }
            else moveBackward(board);
        }
        else if(strlen(input) == 3) break;
        else{
            int ind = addInputMove(board, input);
            if(ind == -1){
                printf("invalid move\n");
                continue;
            }
            MoveNode *move = board->currMove->children->arr[ind];
            if(checkForPromotion(move)){
                int color = getColor(move->pieceList[0]);
                char nameH = color == -1 ? 'h' : 'H';
                char nameQ = color == -1 ? 'q' : 'Q';
                printf("%s%c: [1], %c: [2]\n", promoteString, nameQ, nameH);
                char c = *getPromoInput();
                promotePawnMove(move, c == '1' ? nameQ : nameH, board);
            }
            //incase i want to record the game
            //saveGame(board, "./saved/promotion.txt");
            moveForward(board, ind);
        }
        updateDisplay(board, 1);
        printDisplay(board);
    }
    /*char* moveString = calloc(1, sizeof(char));
    int size = strlen(moveString);
    moveString = realloc(moveString, size + 5); 
    int ind = 0;
    while(moveString[size++] = input[ind++]);
    free(input);
    */
}
int getForwardInput(){
    return 0;
}

char *getInput(){
    char *input = calloc(6, sizeof(char));
    char *endString = "end";
    while(1){
        fgets(input, 6, stdin);
        int ind = 0;
        while(input[ind]){
            if(input[ind] == '\n') input[ind] = '\0';
            ind++;
        }
        if(ind == 2 && (*input == 'F' || *input== 'B')) return input;
        if(ind == 4 && !strcmp(input, endString)) return input;
        if(ind == 5 && validateMove(input)) return input;
        else puts("invalid input");
    }
    return NULL;
}
char *getPromoInput(){
    char *input = calloc(3, sizeof(char));
    while(1){
        fgets(input, 3, stdin);
        if(*input == '1' || *input == '2') return input;
        else puts("invalid input");
    }
    return NULL;
}
int validateMove(char *m){
    return (strlen(m) == 4 &&
    m[0] > 96 && m[0] < 105 &&
    m[1] > 48 && m[1] < 57 &&
    m[2] > 96 && m[2] < 105 &&
    m[3] > 48 && m[3] < 57);
}
/*void printMoves(){
    char *ptr = moveString;
    int len = strlen(moveString);
    for(int x = 0; x < len; x+=4){
        printf("%c%c%c%c\n", ptr[x+0], ptr[x+1], ptr[x+2], ptr[x+3]);
    }
}*/
