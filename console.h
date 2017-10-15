#ifndef CONSOLE_H
#define CONSOLE_H

#define SCREEN_WIDTH  40
#define SCREEN_HEIGHT 25

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

void gotoxy(int x, int y);

void setColor (int foreground, int background);

void resetColor();

void clearScreen();

void initScreen();

void resetScreen();

char getKeyInput();

#endif