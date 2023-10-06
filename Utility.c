#include<stdlib.h>
#include"Utility.h"

struct Tile tile_bucket[TILE_BUCKET_MAX];
int tile_bucket_size;
void InitRandomTile(){
    tile_bucket_size=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<4;j++){
            tile_bucket[tile_bucket_size]=(struct Tile){.exist=1,.type=MANZU,.num=i+1};
            tile_bucket_size++;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<4;j++){
            tile_bucket[tile_bucket_size]=(struct Tile){.exist=1,.type=PINZU,.num=i+1};
            tile_bucket_size++;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<4;j++){
            tile_bucket[tile_bucket_size]=(struct Tile){.exist=1,.type=SOUZU,.num=i+1};
            tile_bucket_size++;
        }
    }
    for(int i=0;i<7;i++){
        for(int j=0;j<4;j++){
            tile_bucket[tile_bucket_size]=(struct Tile){.exist=1,.type=JIHAI,.num=i};
            tile_bucket_size++;
        }
    }
}
struct Tile RandomTile(){
    int r=rand()%tile_bucket_size;
    struct Tile ret=tile_bucket[r];
    tile_bucket[r]=tile_bucket[tile_bucket_size-1];
    tile_bucket[tile_bucket_size-1]=NaN_TILE;
    tile_bucket_size--;
    return ret;
}
void InsertTile(struct Tile t){//消したけど手牌に入らなかったタイルは再利用する。
    tile_bucket[tile_bucket_size]=t;
    tile_bucket_size++;
}

char* TileToStr(struct Tile t){
    if(t.exist==0){
        return "＿";
    }
    if(t.type==MANZU){
        switch(t.num){
        case 1:
            return "\x1b[31m一\x1b[0m";
        case 2:
            return "\x1b[31m二\x1b[0m";
        case 3:
            return "\x1b[31m三\x1b[0m";
        case 4:
            return "\x1b[31m四\x1b[0m";
        case 5:
            return "\x1b[31m五\x1b[0m";
        case 6:
            return "\x1b[31m六\x1b[0m";
        case 7:
            return "\x1b[31m七\x1b[0m";
        case 8:
            return "\x1b[31m八\x1b[0m";
        case 9:
            return "\x1b[31m九\x1b[0m";
        default:
            return "無";
        }
    }else if(t.type==SOUZU){
        switch(t.num){
        case 1:
            return "\x1b[32m１\x1b[0m";
        case 2:
            return "\x1b[32m２\x1b[0m";
        case 3:
            return "\x1b[32m３\x1b[0m";
        case 4:
            return "\x1b[32m４\x1b[0m";
        case 5:
            return "\x1b[32m５\x1b[0m";
        case 6:
            return "\x1b[32m６\x1b[0m";
        case 7:
            return "\x1b[32m７\x1b[0m";
        case 8:
            return "\x1b[32m８\x1b[0m";
        case 9:
            return "\x1b[32m９\x1b[0m";
        default:
            return "無";
        }
    }else if(t.type==PINZU){
        switch(t.num){
        case 1:
            return "① ";
        case 2:
            return "② ";
        case 3:
            return "③ ";
        case 4:
            return "④ ";
        case 5:
            return "⑤ ";
        case 6:
            return "⑥ ";
        case 7:
            return "⑦ ";
        case 8:
            return "⑧ ";
        case 9:
            return "⑨ ";
        default:
            return "無";
        }
    }else{
        switch(t.num){
        case TON:
            return "東";
        case NAN:
            return "南";
        case SHA:
            return "西";
        case PEI:
            return "北";
        case HAKU:
            return "白";
        case HATSU:
        return "\x1b[32m發\x1b[0m";
        case CHUN:
            return "\x1b[31m中\x1b[0m";
        default:
            return "無";
        }
    }
}

char* TileToPlainStr(struct Tile t){
    if(t.exist==0){
        return "＿";
    }
    if(t.type==MANZU){
        switch(t.num){
        case 1:
            return "一";
        case 2:
            return "二";
        case 3:
            return "三";
        case 4:
            return "四";
        case 5:
            return "五";
        case 6:
            return "六";
        case 7:
            return "七";
        case 8:
            return "八";
        case 9:
            return "九";
        default:
            return "無";
        }
    }else if(t.type==SOUZU){
        switch(t.num){
        case 1:
            return "１";
        case 2:
            return "２";
        case 3:
            return "３";
        case 4:
            return "４";
        case 5:
            return "５";
        case 6:
            return "６";
        case 7:
            return "７";
        case 8:
            return "８";
        case 9:
            return "９";
        default:
            return "無";
        }
    }else if(t.type==PINZU){
        switch(t.num){
        case 1:
            return "①";
        case 2:
            return "②";
        case 3:
            return "③";
        case 4:
            return "④";
        case 5:
            return "⑤";
        case 6:
            return "⑥";
        case 7:
            return "⑦";
        case 8:
            return "⑧";
        case 9:
            return "⑨";
        default:
            return "無";
        }
    }else{
        switch(t.num){
        case TON:
            return "東";
        case NAN:
            return "南";
        case SHA:
            return "西";
        case PEI:
            return "北";
        case HAKU:
            return "白";
        case HATSU:
        return "發";
        case CHUN:
            return "中";
        default:
            return "無";
        }
    }
}

char* WindToStr(enum JIHAI_TYPE x){
    switch(x){
    case TON:
        return "東";
    case NAN:
        return "南";
    case SHA:
        return "西";
    case PEI:
        return "北";
    default:
        return "無";
    }
}
void SwapTiles(struct Tile* a,struct Tile* b){
    struct Tile temp=*a;
    *a=*b;
    *b=temp;
}
int TileCmp(struct Tile a,struct Tile b){
    //a-bを返すイメージ。
    //a>bで1,a=bで0、a<bで-1
    if(a.type>b.type){
        return 1;
    }else if(a.type<b.type){
        return -1;
    }else{
        if(a.num>b.num){
            return 1;
        }else if(a.num==b.num){
            return 0;
        }else{
            return -1;
        }
    }
}
void SortTiles(struct Tile* begin,int len){
    //nが小さいので、バブルソート。
    while(1){
        int f=0;
        for(int i=0;i<len-1;i++){
            if(TileCmp(begin[i],begin[i+1])>0){
                SwapTiles(&begin[i],&begin[i+1]);
                f=1;
            }
        }
        if(!f){
            break;
        }
    }
}
void TileSortTest(){
    struct Tile tiles[10];
    for(int i=0;i<10;i++){
        tiles[i]=RandomTile();
        printf("%s",TileToStr(tiles[i]));
    }
    printf("\r\n");
    SortTiles(tiles,10);
    for(int i=0;i<10;i++){
        printf("%s",TileToStr(tiles[i]));
    }
    printf("\r\n");
}

struct Tile NextTile(struct Tile t){
    if(t.type!=JIHAI){
        t.num++;
        if(t.num==10){
            t.num=1;
        }
    }else{
        t.num++;
        if(t.num==7){
            t.num=0;
        }
    }
    return t;
}