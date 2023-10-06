#include<stdio.h>
#include"Tile.h"
#ifndef _H_UTILITY_
#define _H_UTILITY_
//便利変数・関数。
#define TILE_BUCKET_MAX 136
extern struct Tile tile_bucket[TILE_BUCKET_MAX];
extern int tile_bucket_size;
extern void InitRandomTile();
extern void InsertTile();
extern struct Tile RandomTile();
extern char* TileToStr(struct Tile);
extern char* TileToPlainStr(struct Tile);
extern char* WindToStr(enum JIHAI_TYPE x);
extern int TileCmp(struct Tile a,struct Tile b);
extern void SwapTiles(struct Tile* a,struct Tile* b);
extern void SortTiles(struct Tile* begin,int len);
extern void TileSortTest();
extern struct Tile NextTile(struct Tile t);
#endif