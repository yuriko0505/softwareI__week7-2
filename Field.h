#include"Tile.h"
#ifndef _H_FIELD_
#define _H_FIELD_

//盤面の定義
#define WIDTH 8
#define HEIGHT 8
extern struct Tile field[HEIGHT][WIDTH];
extern int x;
extern int y;
#define DEFAULT_X 3
#define DEFAULT_Y 0
extern char input[100];
extern struct Tile dora_tile;
extern struct Tile ura_dora_tile;
extern int round_wind,player_wind;
extern int move_cnt;

#define MAX_TURN 80
extern int turn_cnt;
extern int ippatsu_flag;

//手牌の定義
#define HAND_SIZE 14
extern struct Tile hand_tile[HAND_SIZE]; //ここに消したものを格納してください。
extern int hand_num;
#endif