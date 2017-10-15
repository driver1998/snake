#ifndef QUEUE
#define QUEUE

#include <common.h>
#include <stdbool.h>
typedef struct QNode{
    ElemType data;
    struct QNode* next;
} QNode;

typedef struct queue{
    QNode* front;
    QNode* rear;
} Queue;

bool Queue_Init(Queue* Q);

bool Queue_EnQueue(Queue* Q, ElemType value);

ElemType Queue_GetFront(Queue* Q);

ElemType Queue_GetRear(Queue* Q);

ElemType Queue_DeQueue(Queue* Q);

bool Queue_Clear(Queue* Q);

bool Queue_IsEmpty(Queue Q);

#endif