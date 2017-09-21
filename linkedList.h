#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>
#include <common.h>

typedef struct node{
    ElemType data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct {
    struct node* head;
    struct node* tail;
} LinkedList;

bool LinkedList_Init (LinkedList* head);

bool LinkedList_InsertFirst (LinkedList* list, ElemType value, int i);

bool LinkedList_InsertLast (LinkedList* list, ElemType value, int i);

bool LinkedList_DeleteFirst (LinkedList* list, int i);

bool LinkedList_DeleteLast (LinkedList* list, int i);

ElemType LinkedList_GetFirst (LinkedList list, int i);

ElemType LinkedList_GetLast (LinkedList list, int i);

int LinkedList_Length (LinkedList list);

void LinkedList_Traverse (LinkedList list, void (*visit)(Node* node));

void LinkedList_TraverseReverse (LinkedList list, void (*visit)(Node* node));

bool LinkedList_Clear (LinkedList* list);

#endif