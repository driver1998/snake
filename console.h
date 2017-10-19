#ifndef CONSOLE_H
#define CONSOLE_H

//屏幕宽高
//todo: 把这个宏改成读取实际宽高的函数
#define SCREEN_WIDTH  40
#define SCREEN_HEIGHT 25

//屏幕颜色定义
#ifdef _WIN32
    #define RED   4
    #define GREEN 2
    #define BLUE  1
#else
    #define RED   1
    #define GREEN 2
    #define BLUE  4
#endif

#define YELLOW RED|GREEN
#define PURPLE RED|      BLUE
#define CYAN       GREEN|BLUE
#define WHITE  RED|GREEN|BLUE
#define BLACK 0

//移动光标到(x,y)
void gotoxy(int x, int y);

//设置颜色
void setColor (int foreground, int background);

//重置屏幕颜色
void resetColor();

//清屏
void clearScreen();

//初始化
void initScreen();

//重置屏幕设置为系统默认值
void resetScreen();

//获取键盘输入
char getKeyInput();

#endif