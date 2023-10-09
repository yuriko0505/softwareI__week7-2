#include<stdio.h>
#include<string.h>
#include"Tile.h"
#include"Field.h"
#include"Utility.h"
#ifndef _H_JUDGE
#define _H_JUDGE
extern int count_run;
extern int count_triple;
extern int count_yaojiu_triple;//么九牌の暗刻
extern char yaku[200];
extern char yakuman[200];
extern char score_name[100];
extern int fu;
extern int score;
extern struct Tile sorted_hand_tile[HAND_SIZE];
int Judge_RiichiIppatsuTsumo();
int Judge_Ipeko_Ryanpeko();
int Judge_Pinf();
int Judge_Tanyao();
int Judge_Yakuhai();
int Judge_Chanta_Jyunchan();
int Judge_Honroto();
int Judge_Ikkitsukan();
int Judge_Sansyokudojun();
int Judge_Sansyokudoko();
int Judge_Sananko_Suanko();
int Judge_Shosangen();
int Judge_Honiso();
int Judge_Chiniso_Tsuiso();
int Judge_Chinroutou();
int Judge_Churenpoto();
int Judge_Ryuiso();
int Judge_Shosusi_Daisusi();
int Judge_Dora();
int CalcScore(int han);
void Judge();
#endif