#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
const char *inputString = "INPUT LIST\n"
"move: [letter][number][letter][number]\n"
"go forward: F\n"
"go back: B\n"
"end game: end\n";
void addMove();
char *playGame();
int validateMove(char *m);
int parseInput(char *m);

int main(){
    playGame();
    return 1;
}

char *playGame(){
    Board *board = createBoard();
    boardInit(board);
    updateDisplay(board, 0);
    printDisplay(board);
    printf(inputString); 
    return NULL;
    /*char* moveString = calloc(1, sizeof(char));
    int size = strlen(moveString);
    moveString = realloc(moveString, size + 5); 
    int ind = 0;
    while(moveString[size++] = input[ind++]);
    free(input);
    */
}

char *getInput(){
    char *input = calloc(5, sizeof(char));
    char *endString = "end";
    while(1){
        fgets(input, 5, stdin);
        int ind = 0;
        while(input[ind]){
            if(input[ind] == '\n') input[ind] = '\0';
            ind++;
        }
        if(ind == 2 && (*input == 'F' || *input=='B')) return input;
        if(ind == 4 && !strcmp(input, endString)) return input;
        if(ind == 5 && validateMove(input)) return input;
        else puts("invalid move");
    }
    return NULL;
}
int validateMove(char *m){
    return (strlen(m) != 4 ||
    m[0] > 72 || m[0] < 65 ||
    m[2] > 72 || m[2] < 65 ||
    m[1] > 56 || m[1] < 49 ||
    m[3] > 56 || m[3] < 49); 
}
/*void printMoves(){
    char *ptr = moveString;
    int len = strlen(moveString);
    for(int x = 0; x < len; x+=4){
        printf("%c%c%c%c\n", ptr[x+0], ptr[x+1], ptr[x+2], ptr[x+3]);
    }
}*/
