#include <stdio.h>
#include <stdlib.h>

#include <linkedList.h>

bool LinkedList_Init (LinkedList* list) {
	list->head = NULL;
	list->tail = NULL;
}

bool LinkedList_InsertFirst (LinkedList* list, ElemType value, int n) {
    Node* current = list->head;
    Node* prev = NULL;
   
    if (n<0) return false;
    
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    
    int i=0;
    while (current != NULL) {
        if (i == n) break;
        
        prev = current;
        current = current->next;
        i++;
    }
       
    node->next = current;
    node->prev = prev;
    
    if (prev    == NULL) {
        list->head = node;
    } else {
        prev->next = node;
    }
    
    if (current == NULL) {
        list->tail = node;
    } else {
        current->prev = node;
    }
    
    return true;
}

bool LinkedList_InsertLast (LinkedList* list, ElemType value, int n) {
    Node* current = list->tail;
    Node* next = NULL;
   
    if (n<0) return false;
    
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    
    int i=0;
    while (current != NULL) {
        if (i == n) break;
        
        next = current;
        current = current->prev;
        i++;
    }
       
    node->next = next;
    node->prev = current;
    
    if (current == NULL) {
        list->head = node;
    } else {
        current->next = node;
    }
    
    if (next == NULL) {
        list->tail = node;
    } else {
        next->prev = node;
    }
    
    return true;
}

bool LinkedList_DeleteFirst (LinkedList* list, int n) {
    Node* current = list->head;
    
    if (current == NULL || n<0) return false;
    
    int i=0, overflow=1;
    while (current != NULL) {
        if (i == n) { overflow=0; break; }
        
        current = current->next;
        i++;
    }
    
    if (overflow) return false;
    
    Node* prev = current->prev;
    Node* next = current->next;
    
    if (prev != NULL) {
        prev->next = next;
    } else {
        list->head = next;
    }
    
    if (next != NULL) {
        next->prev = prev;
    } else {
        list->tail = prev;
    }
    
    free(current);
    
    return true;
}

bool LinkedList_DeleteLast (LinkedList* list, int n) {
    Node* current = list->tail;
    
    if (current == NULL || n<0) return false;
    
    int i=0, overflow=1;
    while (current != NULL) {
        if (i == n) { overflow=0; break; }
        
        current = current->prev;
        i++;
    }
    
    if (overflow) return false;
    
    Node* prev = current->prev;
    Node* next = current->next;
    
    if (prev != NULL) {
        prev->next = next;
    } else {
        list->head = next;
    }
    
    if (next != NULL) {
        next->prev = prev;
    } else {
        list->tail = prev;
    }
    
    free(current);
    
    return true;
}

ElemType LinkedList_GetFirst (LinkedList list, int n) {
    Node* current = list.head;
    if (current == NULL || n<0) return false;
    
    int i=0, overflow=1;
    while (current != NULL) {
        if (i == n) { overflow=0; break; }
        
        current = current->next;
        i++;
    }
    
    if (overflow) return ElemType_NUL;
    
    return current->data;
}

ElemType LinkedList_GetLast (LinkedList list, int n) {
    Node* current = list.tail;
    if (current == NULL || n<0) return false;
    
    int i=0, overflow=1;
    while (current != NULL) {
        if (i == n) { overflow=0; break; }
        
        current = current->prev;
        i++;
    }
    
    if (overflow) return ElemType_NUL;
    
    return current->data;
}

int LinkedList_Length (LinkedList list) {
    Node* current = list.head;
    if (current == NULL) return 0;
    
    int i=0;
    while (current != NULL) {
        current = current->next;
        i++;
    }
    
    return i;
}

void LinkedList_Traverse (LinkedList list, void (*visit)(Node* node)) {
    Node* current = list.head;
    if (current == NULL) return;
    
    while (current != NULL) {
        (*visit)(current);
        current = current->next;
    }
}

void LinkedList_TraverseReverse (LinkedList list, void (*visit)(Node* node)) {
    Node* current = list.tail;
    if (current == NULL) return;
    
    while (current != NULL) {
        (*visit)(current);
        current = current->prev;
    }
}

bool LinkedList_Clear (LinkedList* list) {
    Node* current = list->head;
    Node* next;
    if (current == NULL) return false;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
    
    return true;
}