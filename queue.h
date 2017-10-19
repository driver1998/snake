//链队列实现 ElemType类型定义见common.h

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

//队列初始化
bool Queue_Init(Queue* Q);

//入队
bool Queue_EnQueue(Queue* Q, ElemType value);

//取队首
ElemType Queue_GetFront(Queue* Q);

//取队尾
ElemType Queue_GetRear(Queue* Q);

//出队
ElemType Queue_DeQueue(Queue* Q);

//队列清空
bool Queue_Clear(Queue* Q);

//判断队列是否为空
bool Queue_IsEmpty(Queue Q);

#endif