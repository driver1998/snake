#include <stdio.h>
#include <stdlib.h>

#include <common.h>
#include <queue.h>
#include <console.h>
#include <thread.h>

//生成蛇
Snake* initSnake();

//生成果
void newFruit(Point* fruit);

//画点
void drawPoint(int x, int y, Item item);

//读取键盘输入的循环
void controlLoop();	

//游戏主循环
Result gameLoop();

//碰撞检测
bool isHit(int objectX, int objectY, Snake* snake);

volatile Direction _direction = DIRECTION_RIGHT;
Snake* _snake = NULL;
Point* _fruit = NULL;
Thread _thread;
int _score;

int main() {
    
    initScreen();
    newThread(&_thread, controlLoop);

    clearScreen();
    _snake = initSnake();
    _fruit = (Point*)malloc(sizeof(Point));
    newFruit(_fruit);
    _score=0;
    
    gameLoop();
    
    resetScreen();
    printf ("GAME OVER\nSCORE: %d\n", _score);
    return 0;
}


void controlLoop() {
	char c;
	while (true) {

		c = getKeyInput();

		switch (c) {
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
			break;
		}

		if (_direction == DIRECTION_EXIT) break;
	}
}

Result gameLoop() {

	Result result = RESULT_DEFAULT;

	while (true) {

		msleep(100);
		fflush(stdout);

		Point* snakeHead = Queue_GetRear(_snake);

		int newX = snakeHead->x;
		int newY = snakeHead->y;

		switch (_direction) {
		case DIRECTION_UP:
			newY--;
			break;
		case DIRECTION_DOWN:
			newY++;
			break;
		case DIRECTION_LEFT:
			newX--;
			break;
		case DIRECTION_RIGHT:
			newX++;
			break;
		case DIRECTION_EXIT:
			result = RESULT_EXIT;
			goto end;
		}

		if (newX>SCREEN_WIDTH) newX = 1;
		if (newX<1) newX = SCREEN_WIDTH;

		if (newY>SCREEN_HEIGHT) newY = 1;
		if (newY<1) newY = SCREEN_HEIGHT;

		//新的蛇头位置和原来的蛇身撞一起了 GAME OVER
		if (isHit(newX, newY, _snake)) {
			result = RESULT_GAME_OVER;
			_direction = DIRECTION_EXIT;
			goto end;
		}


		Point* newSnakeHead;
		//判断是否吃到
		if (_fruit != NULL && _fruit->x == newX && _fruit->y == newY) {
			//吃到了 创建一个新的蛇头
			newSnakeHead = (Point*)malloc(sizeof(Point));
			newFruit(_fruit);
			_score++;
		}
		else {
			//没吃到 即是正常移动 
			//将蛇尾出队，设置为蛇头的坐标，再入队
			newSnakeHead = Queue_DeQueue(_snake);
			drawPoint(newSnakeHead->x, newSnakeHead->y, ITEM_NULL);
		}

		newSnakeHead->x = newX;
		newSnakeHead->y = newY;
		newSnakeHead->item = ITEM_SNAKE;

		drawPoint(newX, newY, ITEM_SNAKE);
		Queue_EnQueue(_snake, newSnakeHead);
	}

end:
	return result;
}

Snake* initSnake() {    
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    Queue_Init(snake);

    for (int i=1; i<=7; i++) {
        Point* point = (Point*)malloc(sizeof(Point));
        point->x = i;
        point->y = 1;
        point->item = ITEM_SNAKE;
        drawPoint(point->x, point->y, point->item);
        
        Queue_EnQueue(snake, point);
    }
    
    return snake;
}

void newFruit(Point* fruit) {
	if (fruit == NULL) return;

	srand(time(NULL));

	int fruitX, fruitY;
	bool isApproved = false;  //取到的坐标点是否符合要求

	//要求：果坐标不能与蛇身冲突
	while (!isApproved) {

		fruitX = (rand() % (SCREEN_WIDTH - 1)) + 1;
		fruitY = (rand() % (SCREEN_HEIGHT - 1)) + 1;

		if (isHit(fruitX, fruitY, _snake))
			continue;
		else
			isApproved = true;
	}

	fruit->x = fruitX;
	fruit->y = fruitY;
	fruit->item = ITEM_FRUIT;
	drawPoint(fruitX, fruitY, ITEM_FRUIT);
}

void drawPoint(int x, int y, Item item) {
    resetColor();
    gotoxy(x*2-1, y);

    int background = BLACK;
    switch(item) {
        case ITEM_FRUIT:
            background = RED;
            break;
        case ITEM_SNAKE:
            background = YELLOW;
            break;
    }

    setColor(WHITE, background);
    printf("  ");
    resetColor();
}

bool isHit(int objectX, int objectY, Snake* snake) {
    if (snake == NULL) return true;
    
    bool hit = false;
    
    QNode* current = _snake->front;
    while(current != NULL) {
        Point* p = current->data;
        if (p->x == objectX && p->y == objectY) {
            hit = true;
            break;
        }
        current = current->next;
    }
    
    return hit;
}