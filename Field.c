#include"Field.h"
struct Tile field[HEIGHT][WIDTH];
int x;
int y;
char input[100];
struct Tile dora_tile,ura_dora_tile;
struct Tile hand_tile[HAND_SIZE];
int round_wind,player_wind;
int hand_num;
int move_cnt;
int turn_cnt;
int ippatsu_flag;