#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Title.h"
#include"Tile.h"
#include"Field.h"
#include"Utility.h"
#include"Judge.h"
#include"Ranking.h"

void Init(){
    InitRandomTile();
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            field[i][j]=NaN_TILE;
        }
    }
    round_wind=rand()%2;
    player_wind=rand()%4;
    dora_tile=RandomTile();
    ura_dora_tile=RandomTile();
    x=DEFAULT_X;
    y=DEFAULT_Y;
    field[y][x]=RandomTile();
    hand_num=0;
    for(int i=0;i<12;i++){
        hand_tile[i]=NaN_TILE;
    }
    hand_tile[12]=hand_tile[13]=RandomTile();
    move_cnt=0;
    count_run=0;
    count_triple=0;
    turn_cnt=0;
    ippatsu_flag=0;
}

//ゲームに必要な情報を描画する関数
void Draw(){
    if(system("clear")){
        fprintf(stderr,"Error: system(\"clear\") failed");
    }
    printf("%s1局 %s家 ドラ表示牌: %s 残り%d牌\r\n\r\n",WindToStr(round_wind),WindToStr(player_wind),TileToStr(dora_tile),MAX_TURN-turn_cnt);
    for(int i=0;i<HEIGHT;i++){
        printf("  \x1b[42m  \x1b[49m"); //枠線を緑に
        for(int j=0;j<WIDTH;j++){
            if(i==y&&j==x){
                printf("\x1b[1m%s\x1b[0m",TileToStr(field[i][j]));
            }else{
                printf("%s",TileToStr(field[i][j]));
            }
        }
        printf("\x1b[42m  \x1b[49m");
        if(i==1){
            printf("   【操作方法】");
        }else if(i==2){
            printf("   Aキー: 左へ");
        }else if(i==3){
            printf("   Dキー: 右へ");
        }else if(i==4){
            printf("   Sキー: 落下");
        }else if(i==5){
            printf("   .キー: 終了");
        }else if(i==7){
            if(9<=hand_num&&hand_num<12){
                printf("   \x1b[31;43m!!!立直!!!\x1b[0m");
            }else if(hand_num==12){
                printf("   \x1b[31;43m!!!ツモ!!!\x1b[0m");
            }
        }
        printf("\r\n");
    }
    printf("  \x1b[42m  \x1b[49m");
    for(int i=0;i<WIDTH;i++){
        printf("\x1b[42m  \x1b[49m");
    }
    printf("\x1b[42m  \x1b[49m\r\n\r\n");
    

    printf("手牌: ");
    for(int i=0;i<HAND_SIZE;i++){
        printf("%s",TileToStr(hand_tile[i]));
        if(i%3==2){
            printf(" ");
        }
    }
    printf("\r\n");
    //printf("(%d, %d): %s\r\n",y,x,TileToStr(field[y][x]));
}
int Judge_erase(int i, int j){
    //i,jにある牌が消せるかどうかを判別する
    //消せなかったら0, 右方向に消せたら1, 下方向に消せたら2を返す
    if (j + 2 < WIDTH){
        if(!(i==y&&j<=x&&x<=j+2)){
            if (field[i][j].exist==1&&field[i][j+1].exist==1&&field[i][j+2].exist==1&&field[i][j].type == field[i][j+1].type && field[i][j].type == field[i][j+2].type){
                return 1;
            }
        }
    }
    if (i + 2 < HEIGHT){
        if (field[i][j].exist==1&&field[i+1][j].exist==1&&field[i+2][j].exist==1&&field[i][j].type == field[i+1][j].type && field[i][j].type == field[i+2][j].type){
            return 2;
        }
    }
    return 0;
}
//入力を受け取り、盤面を更新する関数
int Update(){
    //whileの中身はinputでいい
    if(input[0]=='d'){
        if (field[y][x+1].exist == 0 && x+1 < WIDTH){
            field[y][x+1]=field[y][x]; 
            field[y][x]=NaN_TILE;
            x++;
            move_cnt++;
        }
        else; //何もしない
    }else if(input[0]=='a'){
        if (field[y][x-1].exist == 0 && x-1 > -1){
            field[y][x-1]=field[y][x];
            field[y][x]=NaN_TILE;
            x--;
            move_cnt++;
        }
        else; //何もしない
    }else if(input[0]=='s'){
        while(y+1<HEIGHT&&field[y+1][x].exist == 0){
            field[y+1][x]=field[y][x];
            field[y][x]=NaN_TILE;
            y++;
        }
    }
    if(move_cnt>=5){
        move_cnt=0;
        if(y+1<HEIGHT&&field[y+1][x].exist == 0){
            field[y+1][x]=field[y][x];
            field[y][x]=NaN_TILE;
            y++;
        }
    }
    if (y+1 >= HEIGHT || field[y+1][x].exist == 1 ){
        //もし下にブロックがあるか床ならばブロックを変える
        x = DEFAULT_X;
        y = DEFAULT_Y;
        move_cnt=0;
        turn_cnt++;
        if (turn_cnt==MAX_TURN||field[y][x].exist == 1){
            return 2;
        }
        else{
            field[y][x] = RandomTile();
        }
    }
    int combo = 0;//tmpの何番目にいれるのか識別するために作る あとで使うのでwhileブロックの外側に出しました
    struct Tile tmp[10][10];//牌に入る候補の牌をいれるもの あとで使うのでwhileブロックの外側に出しました
    while(1){
        int flag=0; //削除されたやつが居たら、連鎖が続いてるので、もう一回回す必要がある。
        //削除パート
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                int jud=Judge_erase(i,j);
                if(jud==1){
                    tmp[combo][0] = field[i][j];
                    tmp[combo][1] = field[i][j+1];
                    tmp[combo][2] = field[i][j+2];
                    field[i][j]=field[i][j+1]=field[i][j+2]=NaN_TILE;
                    SortTiles(tmp[combo],3);
                    combo++;
                    flag=1;
                }
                else if (jud==2){
                    tmp[combo][0] = field[i][j];
                    tmp[combo][1] = field[i+1][j];
                    tmp[combo][2] = field[i+2][j];
                    field[i][j]=field[i+1][j]=field[i+2][j]=NaN_TILE;
                    SortTiles(tmp[combo],3);
                    combo++;
                    flag=1;
                }
            }
        }
        //重力パート
        //下から処理した方が一発で済むのでそうやって組む
        while(1){
            int gravity_flag = 0;
            for(int i=HEIGHT-2;i>=0;i--){
                for(int j=WIDTH-1;j>=0;j--){
                    if(i==y&&j==x){
                        continue;
                    }
                    if (field[i][j].exist==1&&field[i+1][j].exist==0){
                        field[i+1][j] = field[i][j];
                        field[i][j] = NaN_TILE;
                        gravity_flag = 1;
                    }
                }
            }
            if (gravity_flag == 0){
                //重力処理終了
                break;
            }
        }   
        if(flag==0){//連鎖終了
            break;
        }
    }
//ToDo: 削除したものが手牌に入るのかを確認する処理を書く
//まず刻子の判定からそのあと順子、tmp配列に入ったものを取り出していく
//comboが配列数を記憶しているはず、その中に3つあるはずです
    for (int i = 0;i < combo; ++i){
        //刻子の処理
        int insert_flag=0;
        if (tmp[i][0].num == tmp[i][1].num && tmp[i][1].num == tmp[i][2].num){
            hand_tile[hand_num] = tmp[i][0];
            hand_tile[hand_num+1] = tmp[i][1];
            hand_tile[hand_num+2] = tmp[i][2];
            hand_num+=3;
            insert_flag=1;
            ++count_triple;
            if(tmp[i][0].type==JIHAI||tmp[i][0].num==1||tmp[i][0].num==9){
                ++count_yaojiu_triple;
            }
        }
        //順子の処理
        else if (tmp[i][0].type != 3){
            if (tmp[i][1].num == tmp[i][0].num+1 && tmp[i][2].num == tmp[i][0].num+2){
                hand_tile[hand_num] = tmp[i][0];
                hand_tile[hand_num+1] = tmp[i][1];
                hand_tile[hand_num+2] = tmp[i][2];
                hand_num+=3;
                insert_flag=1;
                ++count_run;
            }
        }
        if(insert_flag==0){//手牌に追加されない
            InsertTile(tmp[i][0]);
            InsertTile(tmp[i][1]);
            InsertTile(tmp[i][2]);
            if(ippatsu_flag==1){
                ippatsu_flag=0;
            }
        }else{
            if(hand_num==9){
                ippatsu_flag=1;
            }
        }
        if(hand_num+2==HAND_SIZE){
            return 1;   //ゲーム終了
        }
    }
    return 0;
}

void WriteScore(FILE *fp){
    fprintf(fp, "%d,", score);
    for (int i=0;i<HAND_SIZE;++i){
        fprintf(fp, "%s",TileToStr(hand_tile[i]));
    }
    fprintf(fp,",%s\n",yaku);
    fclose(fp);
}

enum GAME_STATE{
    TITLE,GAME,RESULT,GAMEOVER,RANKING
};

int main(){
    if(system("/bin/stty raw onlcr")){
        fprintf(stderr,"Error\n");
        return 1;
    }
    srand((unsigned)time(NULL));
    Init();
    Title_Draw();
    enum GAME_STATE game_state=TITLE;
    while((input[0]=getchar())!='.'){
        if(game_state==TITLE){
            if(Title_Update()==1){
                game_state=GAME;
                Draw();
            }else if(Title_Update()==-1){
                break;
            }else if(Title_Update()==2){
                game_state=RANKING;
                LoadRanking();
                DrawRanking();
            }
            else{
                Title_Draw();
            }
        }
        else if(game_state==RANKING){
            if(input[0]=='d'){
                ranking_top+=3;
                if(ranking_top>=ranking_num){
                    ranking_top=ranking_num-1;
                }
            }else if(input[0]=='a'){
                ranking_top-=3;
                if(ranking_top<0){
                    ranking_top=0;
                }
            }
            if(input[0]=='r'){
                game_state=TITLE;
                Title_Draw();
            }else{
                DrawRanking();
            }
        }
        else if(game_state==GAME){
            int r = Update();
            if(r==1){
                game_state=RESULT;
                break;
            }
            if(r==2){
                game_state=GAMEOVER;
                break;
            }
            else{
                Draw();
            }
        }
    }
    if(system("/bin/stty cooked")){
        fprintf(stderr,"Error\n");
    }
    Draw();
    if (game_state == RESULT){
        Judge();
        FILE *outputfile; 
        if((outputfile = fopen("score.txt", "a"))==NULL){
            return 1;
        }
        WriteScore(outputfile);
    }
    else if (game_state == GAMEOVER){
        printf("GAMEOVER\n");
    }
    return 0;
}