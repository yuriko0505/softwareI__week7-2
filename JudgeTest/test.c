#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"../Tile.h"
#include"../Field.h"
#include"../Utility.h"
#include"../Judge.h"
void Init(){
    InitRandomTile();
    round_wind=rand()%2;
    player_wind=rand()%4;
    dora_tile=RandomTile();
    ura_dora_tile=RandomTile();
    x=DEFAULT_X;
    y=DEFAULT_Y;
    hand_num=0;
    ippatsu_flag=0;
}
int main(){
    srand((unsigned)time(NULL));
    Init();
    char input[1000];
    printf("Input> ");
    fgets(input,sizeof(input),stdin);
    struct Tile t=(struct Tile){.exist=1};
    for(int i=0;i<strlen(input)&&hand_num<HAND_SIZE;i++){
        if(input[i]=='m'){
            t.type=MANZU;
        }else if(input[i]=='p'){
            t.type=PINZU;
        }else if(input[i]=='s'){
            t.type=SOUZU;
        }else if(input[i]=='j'){
            t.type=JIHAI;
        }else if('0'<=input[i]&&input[i]<='9'){
            t.num=input[i]-'0';
            hand_tile[hand_num]=t;
            if(hand_num%3==2){
                if(hand_tile[hand_num-1].num!=hand_tile[hand_num].num){
                    count_run++;
                }else{
                    count_triple++;
                }
            }
            hand_num++;
        }
    }
    for(int i=0;i<HAND_SIZE;i++){
        printf("%s",TileToStr(hand_tile[i]));
    }
    printf("\n");
    for(int i=0;i<15;i++){
        printf("=");
    }
    printf("\n");
    Judge();
    for(int i=0;i<15;i++){
        printf("=");
    }
    printf("\nIs it correct?[Y/n]>");
    char c=getchar();
    if(c=='N'||c=='n'){
        FILE *fp;
        if((fp=fopen("./ErrorList/list.txt","a+"))==NULL){
            return 1;
        }
        for(int i=0;i<HAND_SIZE;i++){
            fprintf(fp,"%s",TileToPlainStr(hand_tile[i]));
        }
        fprintf(fp,"\n");
        fclose(fp);
    }
    return 0;
}