#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

bool Queue_Init(Queue* Q) {
    if (Q==NULL) return false;
    Q->front = NULL;
    Q->rear = NULL;
    return true;
}

bool Queue_EnQueue(Queue* Q, ElemType value) {
    bool isEmpty = Queue_IsEmpty(*Q);
    
    QNode* node = (QNode*)malloc(sizeof(QNode));
    node->data = value;
    node->next = NULL;
    if (isEmpty) {
        Q->front = node;
    } else {
        Q->rear->next = node;
    }
    Q->rear = node;
    
    return true;
}

ElemType Queue_GetFront(Queue* Q) {
    if (Queue_IsEmpty(*Q)) return ElemType_NUL;
    
    return Q->front->data;
}

ElemType Queue_GetRear(Queue* Q) {
    if (Queue_IsEmpty(*Q)) return ElemType_NUL;
    
    return Q->rear->data;
}

ElemType Queue_DeQueue(Queue* Q) {
    if (Queue_IsEmpty(*Q)) return ElemType_NUL;
    
    QNode* node = Q->front;
    ElemType value = node->data;
    
    Q->front = node->next;
    if (Q->front == NULL) Q->rear = NULL;
    free(node);
    
    return value;
}

bool Queue_Clear(Queue* Q) {
    if (Q==NULL) return false;
    while (!Queue_IsEmpty(*Q)) {
        Queue_DeQueue(Q);
    }
    return true;
}

bool Queue_IsEmpty(Queue Q) {
    return (Q.front == Q.rear && Q.front == NULL);
}