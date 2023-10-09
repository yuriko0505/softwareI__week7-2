#include"Judge.h"
int count_run;
int count_triple;
int count_yaojiu_triple;
char yaku[200];
char yakuman[200];
char score_name[100];
int fu;
int score;
struct Tile sorted_hand_tile[HAND_SIZE];

int Judge_RiichiIppatsuTsumo(){
    //無条件に成立
    if(ippatsu_flag){
        strcat(yaku, " 立直 一発 門前清自摸");
        return 3;
    }else{
        strcat(yaku, " 立直 門前清自摸");
        return 2;
    }
}

//手牌をソートする前に実行
int Judge_Ipeko_Ryanpeko(){
    //全て同じ場合→二盃口
    if(count_run == 4){
        if(hand_tile[0].type == hand_tile[3].type && hand_tile[0].type == hand_tile[6].type && hand_tile[0].type == hand_tile[9].type){
            if(hand_tile[0].num == hand_tile[3].num && hand_tile[0].num == hand_tile[6].num && hand_tile[0].num == hand_tile[9].num){
                strcat(yaku, " 二盃口");
                return 3;
            }
        }
    }
    //異なる一盃口の組を数える
    int count_peko = 0;
    int peko_type = -1;
    int peko_head = -1;
    for(int k=0; k<4; ++k){
        if(hand_tile[3*k].type == JIHAI){
            continue;
        }
        for(int l=k+1; l<4; ++l){
            if(hand_tile[3*k].type == hand_tile[3*l].type){
                if(hand_tile[3*k].num == hand_tile[3*l].num){
                    if(hand_tile[3*k+1].num == hand_tile[3*k].num + 1 && hand_tile[3*k+1].num == hand_tile[3*l+1].num){
                        if(hand_tile[3*k].type != peko_type || hand_tile[3*k].num != peko_head){
                            peko_type = hand_tile[3*k].type;
                            peko_head = hand_tile[3*k].num;
                            ++count_peko;
                        }
                    }
                }
            }
        }
    }   
    if(count_peko == 1){
        strcat(yaku, " 一盃口");
        return 1;
    }else if(count_peko == 2){
        strcat(yaku, " 二盃口");
        return 3;
    }
    return 0;
}

int Judge_Pinf(){
    if(count_run==4){
        if(sorted_hand_tile[12].type == JIHAI){
            if(sorted_hand_tile[12].num == HAKU || sorted_hand_tile[12].num == HATSU || sorted_hand_tile[12].num == CHUN){
                return 0;
            }
            if(sorted_hand_tile[12].num == round_wind || sorted_hand_tile[12].num == player_wind){
                return 0;
            }
        }
        strcat(yaku, " 平和");
        return 1;
    }
    return 0;
}

int Judge_Tanyao(){
    for(int i=0;i<HAND_SIZE;i++){
        if(sorted_hand_tile[i].exist==0||sorted_hand_tile[i].type==JIHAI){
            return 0;
        }
        if(sorted_hand_tile[i].num==1||sorted_hand_tile[i].num==9){
            return 0;
        }
    }
    strcat(yaku, " 断幺九");
    return 1;
}

int Judge_Yakuhai(){
    int cnt=0;
    for(int i=0;i<12;i+=3){
        if(sorted_hand_tile[i].type==JIHAI&&sorted_hand_tile[i].num==HAKU){
            strcat(yaku, " 役牌:白");
            cnt++;
        }else if(sorted_hand_tile[i].type==JIHAI&&sorted_hand_tile[i].num==HATSU){
            strcat(yaku, " 役牌:發");
            cnt++;
        }else if(sorted_hand_tile[i].type==JIHAI&&sorted_hand_tile[i].num==CHUN){
            strcat(yaku, " 役牌:中");
            cnt++;
        }else if(sorted_hand_tile[i].type==JIHAI){
            //自風
            if(sorted_hand_tile[i].num==round_wind){
                strcat(yaku, " 役牌:場風牌");
                cnt++;
            }
            //場風
            if(sorted_hand_tile[i].num==player_wind){
                strcat(yaku, " 役牌:自風牌");
                cnt++;
            }
        }
    }
    return cnt;
}

int Judge_Honroto(){
    int count_jihai = 0;
    int count_1 = 0;
    int count_9 = 0;
    for(int i=0;i<HAND_SIZE;i++){
        if(sorted_hand_tile[i].type == JIHAI){
            ++count_jihai;
        }
        else if(sorted_hand_tile[i].num == 1){
            ++count_1;
        }
        else if(sorted_hand_tile[i].num == 9){
            ++count_9;
        }
    }
    if(count_jihai){
        if(count_1 + count_9 + count_jihai == 14){
            strcat(yaku, " 混老頭");
            return 2;
        }
    }
    return 0;
}

//手牌をソートする前に実行
int Judge_Chanta_Jyunchan(){
    int flag_jihai = 0;
    for(int k=0; k<4; ++k){
        if(hand_tile[3*k].type == JIHAI){
            ++flag_jihai;
            continue;
        }
        int flag_1or9 = 0;
        for(int i=0; i<3; ++i){
            if(hand_tile[3*k+i].num == 1 || hand_tile[3*k+i].num == 9){
                ++flag_1or9;
            }
        }
        if(flag_1or9 == 0){
            return 0;
        }
    }
    if(flag_jihai){
        strcat(yaku, " 混全帯么九");
        return 2;
    }else{
        strcat(yaku, " 純全帯么九");
        return 3;
    }
}

int Judge_Ikkitsukan(){
    for(int k=0; k<3; ++k){
        if(sorted_hand_tile[k].type == JIHAI || sorted_hand_tile[k].num != 1){
            continue;
        }
        int series = 0;
        for(int i=k+1; i<12; ++i){
            if(sorted_hand_tile[k].type == sorted_hand_tile[i].type){
                if(sorted_hand_tile[i-1].num == sorted_hand_tile[i].num){
                    continue;
                }else if(sorted_hand_tile[i-1].num+1 == sorted_hand_tile[i].num){
                    ++series;
                }
            }
        }
        if(series == 8){
            strcat(yaku, " 一気通貫");
            return 2;
        }
    }
    return 0;
}

//手牌をソートする前に実行
int Judge_Sansyokudojun(){
    if(count_run < 3){
        return 0;
    }
    for(int k=0; k<2; ++k){
        int count_dojun = 0;
        int flag[3] = {0};
        if(hand_tile[3*k].num+1 == hand_tile[3*k+1].num){
            flag[hand_tile[3*k].type] = 1;
            for(int l=k+1; l<4; ++l){
                if(hand_tile[3*k].num == hand_tile[3*l].num && hand_tile[3*l].num+1 == hand_tile[3*l+1].num){
                    if(flag[hand_tile[3*l].type] == 0){
                        flag[hand_tile[3*l].type] = 1;
                        ++count_dojun;
                    }
                }
            }
        }
        if(count_dojun == 2){
            strcat(yaku, " 三色同順");
            return 2;
        }
    }
    return 0;
}

//手牌をソートする前に実行
int Judge_Sansyokudoko(){
    if(count_triple < 3){
        return 0;
    }
    for(int k=0; k<2; ++k){
        if(hand_tile[3*k].type == JIHAI){
            continue;
        }
        int count_doko = 0;
        if(hand_tile[3*k].num == hand_tile[3*k+1].num){
            for(int l=k+1; l<4; ++l){
                if(hand_tile[3*l].type != JIHAI && hand_tile[3*k].num == hand_tile[3*l].num && hand_tile[3*l].num == hand_tile[3*l+1].num){
                    ++count_doko;
                }
            }
        }
        if(count_doko == 2){
            strcat(yaku, " 三色同刻");
            return 2;
        }
    }
    return 0;
}

int Judge_Sananko_Suanko(){
    if(count_triple==4){
        strcat(yakuman, " 四暗刻");
        return 1300;
    }else if(count_triple==3){
        strcat(yaku, " 三暗刻");
        return 2;
    }
    return 0;
}

int Judge_Shosangen(){
    int sangenpi = 0;
    for(int i=0;i<HAND_SIZE;i++){
        if(sorted_hand_tile[i].type==JIHAI){
            if(sorted_hand_tile[i].num==HAKU || sorted_hand_tile[i].num==HATSU || sorted_hand_tile[i].num==CHUN){
                ++sangenpi;
            }
        }
    }
    if(sangenpi==8){
        strcat(yaku, " 小三元");
        return 2;
    }
    //sangenpi==9で大三元
    if(sangenpi==9){
        strcat(yaku, " 大三元");
        return 1300;
    }
    return 0;
}

int Judge_Honiso(){
    //雀頭のみ数牌
    if(sorted_hand_tile[0].type == JIHAI){
        if(sorted_hand_tile[12].type != JIHAI){
            strcat(yaku, " 混一色");
            return 3;
        }
        return 0;
    }else{
        int shupi_type = sorted_hand_tile[0].type;
        int flag_jihai = 0;
        for(int i=1; i<HAND_SIZE; ++i){
            if(sorted_hand_tile[i].type != shupi_type){
                if(sorted_hand_tile[i].type != JIHAI){
                    return 0;
                }else{
                    ++flag_jihai;
                }
            }
        }
        if(flag_jihai){
            strcat(yaku, " 混一色");
            return 3;
        }else{
            return 0;
        }
    }
}

int Judge_Chiniso_Tsuiso(){
    if(sorted_hand_tile[0].type == sorted_hand_tile[11].type && sorted_hand_tile[0].type == sorted_hand_tile[12].type){
        if(sorted_hand_tile[0].type == JIHAI){
            strcat(yakuman, " 字一色");
            return 1300;
        }else{
            strcat(yaku, " 清一色");
            return 6;
        }
    }
    return 0;
}

int Judge_Chinroutou(){
    for(int i=0;i<HAND_SIZE;i++){
        if(sorted_hand_tile[i].type == JIHAI){
            return 0;
        }
        if(sorted_hand_tile[i].num != 1 && sorted_hand_tile[i].num != 9){
            return 0;
        }
    }
    strcat(yakuman, " 清老頭");
    return 1300;
}

int Judge_Churenpoto(){
    if(sorted_hand_tile[0].type == JIHAI){
        return 0;
    }
    else if(sorted_hand_tile[0].type != sorted_hand_tile[11].type || sorted_hand_tile[0].type != sorted_hand_tile[12].type){
        return 0;
    }
    else{
        int judge[10] = {0};
        int pos;
        for (int i=0;i<HAND_SIZE;i++){
            pos = sorted_hand_tile[i].num;
            ++judge[pos];
        }
        if(judge[1]<3 || judge[9]<3) return 0;
        else{
            for(int i=2; i<9; i++){
                if(judge[i]==0){
                    return 0;
                }
            }
            strcat(yakuman, " 九蓮宝燈");
            return 1300;
        }
    }
}

int Judge_Ryuiso(){
    for (int i=0;i<HAND_SIZE;i++){
        if(sorted_hand_tile[i].type != SOUZU){
            if(sorted_hand_tile[i].type != JIHAI || sorted_hand_tile[i].num != HATSU){
                return 0;
            }
        }
        else if(sorted_hand_tile[i].num != 2 && sorted_hand_tile[i].num != 3 && sorted_hand_tile[i].num != 4 && sorted_hand_tile[i].num != 6 && sorted_hand_tile[i].num != 8){
            return 0;
        }
        strcat(yakuman, " 緑一色");
        return 1300;
    }
    return 0;
}

int Judge_Shosusi_Daisusi(){
    int news = 0;
    for(int i=0;i<HAND_SIZE;i++){
        if(sorted_hand_tile[i].type==JIHAI){
            if(sorted_hand_tile[i].num==TON || sorted_hand_tile[i].num==NAN || sorted_hand_tile[i].num==SHA || sorted_hand_tile[i].num==PEI){
                ++news;
            }
        }
    }
    if(news == 11){
        strcat(yakuman, " 小四喜");
        return 1300;
    }
    if(news == 12){
        strcat(yakuman, " 大四喜");
        return 1300;
    }
    return 0;
}

int Judge_Dora(){
    int cnt1=0;
    for(int i=0;i<HAND_SIZE;i++){
        if(TileCmp(sorted_hand_tile[i],NextTile(dora_tile))==0){
            cnt1++;
        }
    }
    if(cnt1){
        char str[100];
        snprintf(str,sizeof(str)," ドラ%d",cnt1);
        strcat(yaku,str);
    }
    int cnt2=0;
    for(int i=0;i<HAND_SIZE;i++){
        if(TileCmp(sorted_hand_tile[i],NextTile(ura_dora_tile))==0){
            cnt2++;
        }
    }
    if(cnt2){
        char str[100];
        snprintf(str,sizeof(str)," 裏ドラ%d",cnt2);
        strcat(yaku,str);
    }
    return cnt1+cnt2;
}

int CalcFu(){
    if(count_run==4){
        //平和
        return 20;
    }
    int ret=20;
    //刻子
    ret+=count_triple*4+count_yaojiu_triple*4;
    //雀頭
    if(hand_tile[12].type==JIHAI){
        //場風
        if(hand_tile[12].num==round_wind){
            ret+=2;
        }
        //自風
        if(hand_tile[12].num==player_wind){
            ret+=2;
        }
        //三元牌
        if(hand_tile[12].num>=HAKU){
            ret+=2;
        }
    }
    //メンゼンツモ
    ret+=12;
    //待ちは面倒なのでなし！
    //1の位切り上げ
    ret=(ret+9)-(ret+9)%10;
    return ret;
}


int CalcScore(int han){
    int r;
    if(han<=4){
        //math.hをインクルードしたくないので。。。
        int p=1;
        for(int i=0;i<han+2;i++){
            p*=2;
        }
        r=fu*p*4;
        //100の倍数に切り上げ
        r=(r+99)-(r+99)%100;
        if(r>8000){
            r=8000;
            strcpy(score_name,"\x1b[4;31m満貫\x1b[0m");
        }
    }else if(han==5){
        r=8000;
        strcpy(score_name,"\x1b[1;31m満貫\x1b[0m");
    }else if(han<8){
        r=12000;
        strcpy(score_name,"\x1b[1;31m跳満\x1b[0m");
    }else if(han<11){
        r=18000;
        strcpy(score_name,"\x1b[1;33m倍満\x1b[0m");
    }else if(han<13){
        r=24000;
        strcpy(score_name,"\x1b[1;33m三倍満\x1b[0m");
    }else{
        r=32000*han/13;
        strcpy(score_name,"\x1b[1;33m役満\x1b[0m");
    }
    if(player_wind==0){//東家は1.5倍
        r*=3;
        r/=2;
    }
    return r;
}

void Judge(){
    int han = 0;
    for(int i=0;i<HAND_SIZE;i++){
        sorted_hand_tile[i]=hand_tile[i];
    }
    SortTiles(sorted_hand_tile, 12);  //雀頭以外をソート
    //13翻
    han += Judge_Sananko_Suanko();
    han += Judge_Chiniso_Tsuiso();
    han += Judge_Chinroutou();
    han += Judge_Churenpoto();
    han += Judge_Ryuiso();
    han += Judge_Shosangen();
    han += Judge_Shosusi_Daisusi();
    if(han/100){
        strcpy(yaku, yakuman);
        han /= 100;
    }else{
        han += Judge_RiichiIppatsuTsumo();
        han += Judge_Tanyao();
        han += Judge_Pinf();
        han += Judge_Ipeko_Ryanpeko();
        han += Judge_Honiso();
        han += Judge_Ikkitsukan();
        han += Judge_Chanta_Jyunchan();
        han += Judge_Sansyokudojun();
        han += Judge_Sansyokudoko();
        han += Judge_Honroto();
        han += Judge_Yakuhai();
        
        //ドラ
        han += Judge_Dora();
    }
    fu=CalcFu();
    score=CalcScore(han);
    printf("裏ドラ表示牌: %s\n",TileToStr(ura_dora_tile));
    printf("役　:%s\n", yaku);
    printf("---Result---\n");
    printf("%d符%d翻 %d点 %s\n",fu,han,score,score_name);
    return;
}