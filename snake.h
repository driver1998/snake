#ifndef SNAKE
#define SNAKE

#define DIRECTION_UP    1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3
#define DIRECTION_RIGHT 4

typedef Queue Snake;
typedef char Item;
typedef int Direction;

const char ITEM_WALL  = '#';
const char ITEM_SNAKE = '*';
const char ITEM_FRUIT = '@';
const char ITEM_NULL  = ' ';


Snake* initSnake();

void drawPoint(int x, int y, Item item);

void* gameLoop();

#endif