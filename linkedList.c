#include <stdio.h>
#include <stdlib.h>

#include <linkedList.h>

bool LinkedList_Init (LinkedList* head) {
    head->next = NULL;
}

bool LinkedList_Insert (LinkedList* head, ElemType value, int n) {
    Node* current = head->next;
    Node* prev = head;
   
    if (n<0 && n!=LAST) return false;
    
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    
    int i=0;
    while (current != NULL) {
        if (i == n) break;
        
        prev = current;
        current = current->next;
        i++;
    }
       
    node->next = current;
    prev->next = node;
    
    return true;
}

bool LinkedList_Delete (LinkedList* head, int n) {
    Node* current = head->next;
    Node* prev = head;
    if (current == NULL || (n<0 && n!=LAST)) return false;
    
    int i=0, overflow=1;
    while (current != NULL) {
        if (i == n) { overflow=0; break; }
        if (n == LAST && current->next == NULL) { overflow=0; break; }
        
        prev = current;
        current = current->next;
        i++;
    }
    
    if (overflow) return false;
    
    prev->next = current->next;
    free(current);
    
    return true;
}

ElemType LinkedList_Get (LinkedList head, int n) {
    Node* current = head.next;
    if (current == NULL || (n<0 && n!=LAST)) return false;
    
    int i=0, overflow=1;
    while (current != NULL) {
        if (i == n) { overflow=0; break; }
        if (n == LAST && current->next == NULL) { overflow=0; break; }
        
        current = current->next;
        i++;
    }
    
    if (overflow) return ElemType_NUL;
    
    return current->data;
}

int LinkedList_Length (LinkedList head) {
    Node* current = head.next;
    if (current == NULL) return 0;
    
    int i=0;
    while (current != NULL) {
        current = current->next;
        i++;
    }
    
    return i;
}

void LinkedList_Traverse (LinkedList head, void (*visit)(Node* node)) {
    Node* current = head.next;
    if (current == NULL) return;
    
    while (current != NULL) {
        (*visit)(current);
        current = current->next;
    }
}

bool LinkedList_Clear (LinkedList* head) {
    Node* current = head->next;
    Node* next = NULL;
    if (current == NULL) return false;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    head->next = NULL;
    
    return true;
}