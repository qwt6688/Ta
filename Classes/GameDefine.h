#ifndef _GameDefine_H_
#define _GameDefine_H_

//定义屏幕宽高，这与所做的图片有关
#define Game_SCREE_WIDTH 480
#define Game_SCREE_HEIGHT 800

//精灵大小
#define SPRITE_WIDTH 40
//边框的大小
#define BOADER_WIDTH 6

//行和列
#define ROWS  10
#define COLS  10

//精灵种类总数
#define TOTAL_SPRITE 8

//普通的精灵
static const char* spriteName[TOTAL_SPRITE] = {
	"q1.png",  
    "q2.png",  
    "q3.png",  
    "q4.png",  
    "q5.png",  
    "q6.png",
	"q7.png",
	"q8.png"
};

#endif