#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>
#include <common.h>

#define LAST -1

typedef struct node{
    ElemType data;
    struct node* next;
} Node, LinkedList;

bool LinkedList_Init (LinkedList* head);

bool LinkedList_Insert (LinkedList* head, ElemType value, int i);

bool LinkedList_Delete (LinkedList* head, int i);

ElemType LinkedList_Get (LinkedList head, int i);

int LinkedList_Length (LinkedList head);

void LinkedList_Traverse (LinkedList head, void (*visit)());

bool LinkedList_Clear (LinkedList* head);

#endif