#ifndef CONSOLE_H
#define CONSOLE_H

//��Ļ���
//todo: �������ĳɶ�ȡʵ�ʿ�ߵĺ���
#define SCREEN_WIDTH  40
#define SCREEN_HEIGHT 25

//��Ļ��ɫ����
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

//�ƶ���굽(x,y)
void gotoxy(int x, int y);

//������ɫ
void setColor (int foreground, int background);

//������Ļ��ɫ
void resetColor();

//����
void clearScreen();

//��ʼ��
void initScreen();

//������Ļ����ΪϵͳĬ��ֵ
void resetScreen();

//��ȡ��������
char getKeyInput();

#endif