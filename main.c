#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <curses.h>
#include <math.h>

#include <common.h>
#include <linkedList.h>
#include <snake.h>
#include <screen.h>


Direction _direction = DIRECTION_RIGHT;
pthread_t _thread;
Snake* _snake = NULL;
Point* _fruit = NULL;

void* controlLoop (){

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
    return NULL;
}

int main() {
    
    initscr();
    
    pthread_create(&_thread, NULL, controlLoop, NULL);
    
    _snake = initSnake();
    
    _fruit = (Point*)malloc(sizeof(Point));
    newFruit(_fruit);
    
    gameLoop();
    
    endwin();
    
    
    printf ("\n\033[2J\nGAME OVER\n");
    return 0;
}

Snake* initSnake() {
    clear();
    
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    LinkedList_Init(snake);

    int i;
    for (i=1; i<=7; i++) {
        Point* point = (Point*)malloc(sizeof(Point));
        point->x = 1;
        point->y = 1;
        point->item = ITEM_SNAKE;
        drawPoint(point->x, point->y, point->item);
        LinkedList_InsertFirst(snake, point, 0);
    }
    
    return snake;
}

void drawPoint(int x, int y, Item item) {
    gotoxy(x, y);
    
    //if (item == ITEM_SNAKE) setColor(YELLOW, YELLOW);
    printf("%c",item);
    resetColor();
}

void newFruit(Point* fruit) {
    if (fruit == NULL) return;
    
    bool isApproved = false;
    int x,y;
    
    while (!isApproved) {
        
        x=(rand()%(SCREEN_WIDTH))+1;
        y=(rand()%(SCREEN_HEIGHT))+1;
        if (x<1 || x>SCREEN_WIDTH || y<1 || y>SCREEN_HEIGHT) goto end;
        
        Node* current = _snake->head;
        while(current != NULL) {
            Point* p = current->data;
            if (p->x == x && p->y == y) {
                goto end;
            }
            current = current->next;
        }
        
        isApproved = true;

        end:
        continue;
    }
    
    fruit->x = x;
    fruit->y = y;
    fruit->item = ITEM_FRUIT;
    drawPoint(x, y, ITEM_FRUIT);
}

void* gameLoop() {

    int i;
    struct timeval time;
    while(true) {
        usleep(1000*100);
        fflush(stdout);

        Point* snakeHead = LinkedList_GetFirst(*_snake, 0);


        
        int x;
        int y;
        
        switch(_direction) {
            case DIRECTION_UP:
                x=snakeHead->x;
                y=snakeHead->y-1;
                break;
            case DIRECTION_DOWN:
                x=snakeHead->x;
                y=snakeHead->y+1;
                break;
            case DIRECTION_LEFT:
                x=snakeHead->x-1;
                y=snakeHead->y;
                break;
            case DIRECTION_RIGHT:
                x=snakeHead->x+1;
                y=snakeHead->y;
                break;
            case DIRECTION_EXIT:
                goto end;
        }
        
        if (x>SCREEN_WIDTH ) x=1;
        if (x<1) x=SCREEN_WIDTH;
        if (y>SCREEN_HEIGHT) y=1;
        if (y<1) y=SCREEN_HEIGHT;
        

        
        Node* current = _snake->head;
        while(current != NULL) {
            Point* p = current->data;
            if (p->x == x && p->y == y) {
                goto end;
            }
            current = current->next;
        }
        
        
        Point* point;
        
        if (_fruit != NULL && _fruit->x == x && _fruit->y == y) {
            point = (Point*)malloc(sizeof(Point));
            newFruit(_fruit);
        } else {
            point = LinkedList_GetLast(*_snake, 0);
            LinkedList_DeleteLast(_snake, 0);
            drawPoint(point->x, point->y, ITEM_NULL);
        }
        
        point->x = x;
        point->y = y;
        point->item = ITEM_SNAKE;
        
        drawPoint(point->x, point->y, point->item);
        LinkedList_InsertFirst(_snake, point, 0);
    }
    
    end:
    clear();
    echo();
    resetColor();
    
    return NULL;
}