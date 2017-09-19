#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include <common.h>
#include <queue.h>
#include <snake.h>
#include <screen.h>


Direction _direction = DIRECTION_DOWN;
//pthread_t _threadID;
Snake* _snake;

int main() {
	_snake = initSnake();
	
	printf("\n");
	
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
		
		printf("\n");

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
				
		}
		
		drawPoint(point->x, point->y, point->item);
		Queue_EnQueue(_snake, point);
		
		
	}
	return NULL;
}

void drawSnake() {
	
}