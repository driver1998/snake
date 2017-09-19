#ifndef SCREEN
#define SCREEN

#define BLACK  0
#define RED    1
#define GREEN  2
#define YELLOW 3
#define BLUE   4
#define PURPLE 5
#define CYAN   6
#define WHITE  7

void gotoxy(int x, int y);

void setColor (int foreground, int background);

void resetColor();

void _clear();

#endif