#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node : 스택에 하나씩 쌓일 데이터
typedef struct tNode {
    char* data;
    struct tNode* next;
} Node;

// LinkedList
typedef struct tLinkedListStack {
    Node* head; // 리스트의 헤드 노드 주소를 가리킬 포인터
    Node* top; // 리스트의 테일 노드 주소를 가리킬 포인터
    int count; // 리스트의 노드 갯수를 저장할 변수
} LinkedListStack;

LinkedListStack* LLS_Stack_Init();
Node* LLS_Node_Init(char* str);

LinkedListStack* LLS_Stack_Init() {
    LinkedListStack* stack;
    stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
    stack->head = NULL;
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

Node* LLS_Node_Init(char* str) {
    // 새로운 노드의 메모리를 힙 영역에 할당
    Node* newNode = (Node*)malloc(sizeof(Node));
    // 노드의 요소(데이터)의 공간을 힙 영역에 할당
    newNode->data = (char*)malloc(strlen(str)+1);
    // 노드의 데이터에 문자열을 복사
    strcpy(newNode->data, str);
    newNode->next = NULL;
}

void LLS_Push(LinkedListStack* list, char* str) {
    Node* newNode = LLS_Node_Init(list,str);

    if(list->head == NULL) {
        list->head = newNode;
    }
    else {
        Node* oldTop = list->head;
        while(oldTop->next != NULL) {
            oldTop = oldTop->next;
        }
        oldTop->next = newNode;
    }
}



int main(void) {
    // stack이라는 리스트를 생성
    LinkedListStack* stack;
    // 함수를 통해 리스트 형태의 스택을 생성
    stack = LLS_Stack_Init();

}