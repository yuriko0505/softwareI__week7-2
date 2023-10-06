#ifndef _H_TILE
#define _H_TILE
//麻雀牌を持つ構造体を定義。
enum TILE_TYPE{
    MANZU, //0
    PINZU, //1
    SOUZU, //2
    JIHAI //3
};
enum JIHAI_TYPE{
    TON,//0
    NAN,//1
    SHA,//2...
    PEI,
    HAKU,
    HATSU,
    CHUN
};
struct Tile{
    enum TILE_TYPE type;//牌の種類
    int num;//牌の番号。type=MANZU、num=2なら2萬
    int exist; //盤面上で存在するか否か。存在しない場合は0
};

extern const struct Tile NaN_TILE;

#endif