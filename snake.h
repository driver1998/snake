#ifndef SNAKE
#define SNAKE

#define DIRECTION_UP    1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3
#define DIRECTION_RIGHT 4
#define DIRECTION_EXIT  -1

#define RESULT_DEFAULT   0
#define RESULT_GAME_OVER 1
#define RESULT_EXIT      2

typedef Queue Snake;
typedef char Item;
typedef int Direction;
typedef int Result;

#define ITEM_WALL  '#'
#define ITEM_SNAKE '*'
#define ITEM_FRUIT '@'
#define ITEM_NULL  ' '


Snake* initSnake();

void drawPoint(int x, int y, Item item);

Result gameLoop();

void newFruit(Point* fruit);

#endif