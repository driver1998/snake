#include <stdio.h>
#include <string.h>
#include <screen.h>

void gotoxy(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

void setColor (int foreground, int background) {
	printf("\033[3%d;4%dm", foreground, background);
}

void resetColor () {
	printf("\033[m");
}

void _clear() {
	printf("\033[2J");
}