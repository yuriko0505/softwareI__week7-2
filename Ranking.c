#include"Ranking.h"
#include <stdlib.h>
int ranking_num;
int ranking_top;
int ranking_index[RANKING_MAX];
int score_list[RANKING_MAX];
char hand_list[RANKING_MAX][1000];
char yaku_list[RANKING_MAX][1000];

void LoadRanking(){
    FILE *fp;
    if((fp=fopen("score.txt","r"))==NULL){
        return;
    }
    ranking_top=0;
    ranking_num=0;
    while(ranking_num<RANKING_MAX&&fscanf(fp,"%d,%[^,],%[^\n]",&score_list[ranking_num],hand_list[ranking_num],yaku_list[ranking_num])!=EOF){
        ranking_num++;
    }
    for(int i=0;i<ranking_num;i++){
        ranking_index[i]=i;
    }
    for(int i=ranking_num;i<RANKING_MAX;i++){
        ranking_index[i]=-1;
    }
    //要素数多くないし…バブルソートで…ええか…。
    while(1){
        int f=0;
        for(int i=0;i<ranking_num-1;i++){
            if(score_list[ranking_index[i]]<score_list[ranking_index[i+1]]){
                int temp=ranking_index[i];
                ranking_index[i]=ranking_index[i+1];
                ranking_index[i+1]=temp;
                f=1;
            }
        }
        if(f==0){
            break;
        }
    }
    fclose(fp);
}
void DrawRanking(){
    if(system("clear")){
        fprintf(stderr,"Error\n");
    }
    printf("### ハイスコアランキング ###\r\n\r\n");
    
    for (int i = ranking_top;i < ranking_top+3;++i){
        if (ranking_index[i]!=-1){
            printf("#%d\r\n\t点数: %d\r\n\t手牌: %s\r\n\t役: %s\r\n",i+1,score_list[ranking_index[i]],hand_list[ranking_index[i]],yaku_list[ranking_index[i]]);
        }
    }
    printf("\r\nAキーで戻る Dキーで進む\r\n");
    printf("Rキーでタイトルに戻る\r\n");
}

