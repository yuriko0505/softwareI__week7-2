#include"Field.h"
#ifndef _H_TITLE
#define _H_TITLE
// タイトルページでの選択肢
enum MODE_TYPE {
    START,
    RANK,
    QUIT
};
extern int Title_Update();
extern void Title_Draw();
#endif
