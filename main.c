#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <curses.h>

#include <common.h>
#include <queue.h>
#include <snake.h>
#include <screen.h>


Direction _direction = DIRECTION_DOWN;
pthread_t thread;
Snake* _snake;

void* controlLoop (){
	initscr();
	noecho();
	char c;
	while (true) {
		c=getch();
		
		switch(c) {
			case 'w':
			case 'W':
				if (_direction != DIRECTION_DOWN) _direction = DIRECTION_UP;
				break;
			
			case 'a':
			case 'A':
				if (_direction != DIRECTION_RIGHT) _direction = DIRECTION_LEFT;
				break;
				
			case 's':
			case 'S':
				if (_direction != DIRECTION_UP) _direction = DIRECTION_DOWN;
				break;
				
			case 'd':
			case 'D':
				if (_direction != DIRECTION_LEFT) _direction = DIRECTION_RIGHT;
				break;
				
			case 'q':
			case 'Q':
				_direction = DIRECTION_EXIT;
				goto end;
		}
	}
	
	end:
	endwin();
	return NULL;
}


int main() {
	_snake = initSnake();
	
	printf("\n");
	
	pthread_create(&thread, NULL, controlLoop, NULL);
	gameLoop();
	return 0;
}

Snake* initSnake() {
	clear();
	
	Snake* snake = (Snake*)malloc(sizeof(Snake));
	Queue_Init(snake);

	int i;
	for (i=1; i<=10; i++) {
		Point* point = (Point*)malloc(sizeof(Point));
		point->x = i;
		point->y = 1;
		point->item = ITEM_SNAKE;
		drawPoint(point->x, point->y, point->item);
		Queue_EnQueue(snake, point);
	}
	
	return snake;
}

void drawPoint(int x, int y, Item item) {
	gotoxy(x, y);
	printf("%c",item);
}

void* gameLoop() {

	int i;
	struct timeval time;
	while(true) {
		usleep(1000*100);
		
		fflush(stdout);

		Point* snakeHead = _snake->rear->data;
		Point* point = Queue_DeQueue(_snake);

		drawPoint(point->x, point->y, ITEM_NULL);
		
		switch(_direction) {
			case DIRECTION_UP:
				point->x=snakeHead->x;
				point->y=snakeHead->y-1;
				if (point->y <1) point->y=25;
				break;
			case DIRECTION_DOWN:
				point->x=snakeHead->x;
				point->y=(snakeHead->y+1)%25;
				break;
			case DIRECTION_LEFT:
				point->x=snakeHead->x-1;
				point->y=snakeHead->y;
				if (point->x <1) point->x=80;
				break;
			case DIRECTION_RIGHT:
				point->x=(snakeHead->x+1)%80;
				point->y=snakeHead->y;
				break;
			case DIRECTION_EXIT:
				goto end;
				
		}
		
		drawPoint(point->x, point->y, point->item);
		Queue_EnQueue(_snake, point);
		
		
	}
	
	end:
	return NULL;
}

void drawSnake() {
	
}