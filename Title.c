#include<stdio.h>
#include<stdlib.h>
#include "Title.h"
#define TITLE_HEIGHT 8
#define TITLE_WIDTH 8
int Title_Update(){
    if(input[0]=='s'){
        return START;
    }else if(input[0]=='r'){
        return RANK;
    }else if(input[0]=='q'){
        return QUIT;
    }
    else return -1;
}
void Title_Draw(){
    printf("\r\n\r\n\r\n");
    for(int i=0;i<TITLE_HEIGHT;i++){
        printf("  \x1b[42m  \x1b[49m");
        if (i == 2){
            printf("  落ちゲー\x1b[31m麻雀\x1b[39m  ");
        }
        else if (i == 4){
            printf("  S: スタート   ");
        }
        else if (i == 5){
            printf("  R: ランキング ");
        }
        else if (i == 6){
            printf("  Q: 終了       ");
        }
        else {for(int j=0;j<TITLE_WIDTH;j++){
            printf("  ");
        }}
        printf("\x1b[42m  \x1b[49m\r\n");
    }
    printf("  \x1b[42m  \x1b[49m");
    for(int i=0;i<TITLE_WIDTH;i++){
        printf("\x1b[42m  \x1b[49m");
    }
    printf("\x1b[42m  \x1b[49m\r\n");
    fprintf(stdout, "\e[%dA", 11);
}