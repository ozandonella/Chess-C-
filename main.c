#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char *pieceNames = "prnbqk";
char **display;
char *whitePieces[16];
char *blackPieces[16];
void initDisplay();
void printDisplay();
int cohpareStrings(char *str1, char *str2);
int moveStringSize = 0;
char *moveString;
void addMove();
void printMoves();
int validateMove(char *m);
int main(){
    display = calloc(17,sizeof(char *));
    //moveString = malloc(1);
    //*moveString = '\0';
    initDisplay();
    printDisplay();
    return 0;
}
void addMove(){
    puts("enter a move [letter][number][letter][number]");
    char *input = malloc(5);
    while(true){
        scanf("%4s",input);
        if(validateMove(input)) break;
        else puts("invalid move");
    }
    int size = strlen(moveString);
    moveString = realloc(moveString, size + 5); 
    int ind = 0;
    while(moveString[size++] = input[ind++]);
    free(input);
}
int validateMove(char *m){
    return (strlen(m) != 4 ||
    m[0] > 72 || m[0] < 65 ||
    m[2] > 72 || m[2] < 65 ||
    m[1] > 56 || m[1] < 49 ||
    m[3] > 56 || m[3] < 49); 
}
void printMoves(){
    char *ptr = moveString;
    int len = strlen(moveString);
    for(int x = 0; x < len; x+=4){
        printf("%c%c%c%c\n", ptr[x+0], ptr[x+1], ptr[x+2], ptr[x+3]);
    }
}

int compareStrings(char *str1, char *str2){
    int val=0;
    while(!(val = *str2++ - *str1++) && (*str2 + *str1));
    return val;
}
void initDisplay(){
    for(int y = 0; y < 17; y++){
        display[y] = malloc(34 * sizeof(char));
        display[y][33] = '\n';
        for(int x = 0; x < 33; x++){
            if(y%2 == 0 && ((y==0||(y==16 && x%4!=2) || (y>0&&y<16&&x>0&&x<32)))) display[y][x] = '-'; 
            else if(y%2==1 && x==0) display[y][x] = (char) ('8' - y/2);
            else if(y==16 && x%4==2) display[y][x] = (char) ('a' + x/4);
            else if(x%4==0) display[y][x] = '|';
            else if((((y/2)%2 + x/4))%2 == 0) display[y][x] = (char) 219;
            else display[y][x] = ' ';
        }
    }
}
void printDisplay(){
    for(int y = 0; y < 17; y++){
        for(int x = 0; x < 34; x++){
            printf("%c", display[y][x]);
        }
    }
}



