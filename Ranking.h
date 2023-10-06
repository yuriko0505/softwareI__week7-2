#include<stdio.h>
#include"Tile.h"
#include"Utility.h"
#ifndef _M_RANKING
#define _M_RANKING
#define RANKING_MAX 1000
extern int ranking_num;    //rankingの要素数
extern int ranking_index[RANKING_MAX]; //k番目には得点k位が何番目の要素かが格納される。
extern int ranking_top;    //何番目から見るか。
extern int score_list[RANKING_MAX];
extern char hand_list[RANKING_MAX][1000];
extern char yaku_list[RANKING_MAX][1000];
void LoadRanking();
void DrawRanking();
#endif