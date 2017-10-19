#ifndef COMMON
#define COMMON

#include <stdbool.h>

//蛇方向的常量定义
#define DIRECTION_UP    1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3
#define DIRECTION_RIGHT 4
#define DIRECTION_EXIT  -1 //特殊值，代表退出游戏

//游戏结果常量定义
#define RESULT_DEFAULT   0
#define RESULT_GAME_OVER 1
#define RESULT_EXIT      2

//坐标类型常量定义
#define ITEM_WALL  '#'
#define ITEM_SNAKE '*'
#define ITEM_FRUIT '@'
#define ITEM_NULL  ' '

//类型定义
#define ElemType      Point*
#define ElemType_NUL  NULL
#define Snake         Queue
typedef char Item;
typedef int Direction;
typedef int Result;

//坐标结构
typedef struct {
	int x;
	int y;
	char item;
	int value;
} Point;


#endif