#include <console.h>

#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>
#else
	#include <curses.h>
#endif

void initScreen() {
	clearScreen();

	#ifdef _WIN32
		CONSOLE_CURSOR_INFO cursorInfo;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleCursorInfo(console, &cursorInfo);
		cursorInfo.bVisible = 0;
		SetConsoleCursorInfo(console, &cursorInfo);
	#else
		initscr();
		noecho();
		printf("\033[?25l");
	#endif
}

void resetScreen() {
	#ifdef _WIN32
		CONSOLE_CURSOR_INFO cursorInfo;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleCursorInfo(console, &cursorInfo);
		cursorInfo.bVisible = 1;
		SetConsoleCursorInfo(console, &cursorInfo);
	#else
		endwin();
	#endif

	resetColor();
	clearScreen();
	gotoxy(1,1);
}

char getKeyInput() {
	return getch();
}

void gotoxy(int x, int y) {
	#ifdef _WIN32
		COORD pos;
		pos.X = x-1;
		pos.Y = y-1;

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(console, pos);
	#else
		printf("\033[%d;%dH", y, x);
	#endif
}

void setColor (int foreground, int background) {
	#ifdef _WIN32
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, foreground | (background << 4));
	#else
		printf("\033[3%d;4%dm", foreground, background);
	#endif
}

void resetColor () {
	setColor(WHITE, BLACK);
}

void clearScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		printf("\033[2J");
	#endif
}