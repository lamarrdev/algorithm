#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct LinkedListStack {
    Node* top;
    int size;
} LinkedListStack;

LinkedListStack* LLS_Stack_Init();
Node* LLS_Node_Init(char* str);
void LLS_Push(LinkedListStack* list, char* str);
void LLS_Pop(LinkedListStack* list);
Node* LLS_Top(LinkedListStack* list);
void LLS_Destroy(LinkedListStack* list);

LinkedListStack* LLS_Stack_Init() {
    LinkedListStack* stack;
    stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

Node* LLS_Node_Init(char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(str)+1);
    strcpy(newNode->data, str);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void LLS_Push(LinkedListStack* list, char* str) {
    Node* newNode = LLS_Node_Init(str);
    Node* oldTop;

    if(list->top == NULL) {
        list->top = newNode;
    }
    else {
        oldTop = list->top;
        oldTop->next = newNode;
        newNode->prev = oldTop;
        list->top = newNode;
    }
    list->size++;
}

void LLS_Pop(LinkedListStack* list) {
    Node* currentTop = list->top;
    Node* newTop;

    if(currentTop == NULL) return;
    else {
        newTop = list->top->prev;
        newTop->next = NULL;
        list->top = newTop;
    }
    list->size--;
    free(currentTop->data);
    free(currentTop);
}

Node* LLS_Top(LinkedListStack* list) {
    return list->top;
}

void LLS_Destroy(LinkedListStack* list) {
    Node* delNode= list->top;
    while(delNode != NULL) {
        list->top = list->top->prev;
        free(delNode->data);
        free(delNode);
        delNode = list->top;
    }
    free(list);
}

int main(void) {
    LinkedListStack* stack;
    stack = LLS_Stack_Init();
    
    printf("Push a node\n");
    LLS_Push(stack, "AAA");
    printf("top : %s\n\n",LLS_Top(stack)->data);

    printf("Push three nodes\n");
    LLS_Push(stack, "BBB");
    LLS_Push(stack, "CCC");
    LLS_Push(stack, "DDD");
    printf("top : %s\n\n",LLS_Top(stack)->data);   

    printf("Pop\n");
    LLS_Pop(stack);
    printf("top : %s\n\n",LLS_Top(stack)->data);

    printf("Pop two nodes\n");
    LLS_Pop(stack);
    LLS_Pop(stack);
    printf("top : %s\n\n",LLS_Top(stack)->data);
    
    LLS_Destroy(stack);

    return 0;
}