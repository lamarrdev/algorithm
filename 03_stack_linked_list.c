#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef int ElementType

// Node : 스택에 하나씩 쌓일 데이터를 정의
typedef struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
} Node;

// LinkedListStack : 스택 형태의 리스트를 정의
typedef struct tLinkedListStack {
    Node* top; // 리스트의 테일 노드 주소를 가리킬 포인터
    int size; // 리스트의 노드 갯수를 저장할 변수
} LinkedListStack;

LinkedListStack* LLS_Stack_Init();
Node* LLS_Node_Init(char* str);
void LLS_Push(LinkedListStack* list, char* str);

// LLS_Stack_Init : 스택 형태의 리스트를 초기화
LinkedListStack* LLS_Stack_Init() {
    LinkedListStack* stack;
    stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

// LLS_Node_Init : 스택에 들어갈 노드를 초기화
Node* LLS_Node_Init(char* str) {
    // 새로운 노드의 메모리를 힙 영역에 할당
    Node* newNode = (Node*)malloc(sizeof(Node));
    // 노드의 요소(데이터)의 공간을 힙 영역에 할당
    newNode->data = (char*)malloc(strlen(str)+1);
    // 노드의 데이터에 문자열을 복사
    strcpy(newNode->data, str);
    // 노드의 포인터를 지정
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// LLS_Push : 리스트(스택)의 테일(마지막 노드)뒤에
// 또는 Top 노드의 위에 새로운 노드를 추가
void LLS_Push(LinkedListStack* list, char* str) {
    // 새로운 노드를 생성
    Node* newNode = LLS_Node_Init(str);
    // oldTop : 현재의 마지막(가장 위) 노드를 보관할 변수
    Node* oldTop;

    // 리스트(스택)에 노드가 없는 경우
    if(list->top == NULL) {
        list->top = newNode;
    }
    // 리스트(스택)에 노드가 있는 경우
    else {
        oldTop = list->top;
        oldTop->next = newNode;
        newNode->prev = oldTop;
        list->top = newNode;
    }
    // 리스트의 노드 갯수를 추가
    list->size++;
}

// LLS_Pop : 리스트(스택)의 Top을 제거
void LLS_Pop(LinkedListStack* list) {
    // currentTop : 제거 전 현재의 Top 노드를 저장할 변수
    Node* currentTop = list->top;
    // newTop : Top 노드가 제거되고 새롭게 Top 노드가 될 변수
    Node* newTop;

    // 리스트(스택)에 노드가 하나도 없는 경우 함수를 종료
    if(currentTop == NULL) return;
    else {
        newTop = list->top->prev;
        newTop->next = NULL;
        list->top = newTop;
    }
    list->size--;
    // 노드의 데이터(문자열)과 노드의 메모리를 해제
    free(currentTop->data);
    free(currentTop);
}

// LLS_Top : 리스트(스택)의 Top을 반환하는 함수
Node* LLS_Top(LinkedListStack* list) {
    return list->top;
}

// LLS_Destroy : 리스트(스택)의 모든 노드와 리스트의 메모리를 해제
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
    // stack이라는 리스트를 생성
    LinkedListStack* stack;
    // 함수를 통해 리스트 형태의 스택을 생성
    stack = LLS_Stack_Init();
    
    // 1개의 노드를 푸쉬
    printf("Push a node\n");
    LLS_Push(stack, "AAA");
    // stack 리스트 top의 데이터를 출력
    printf("top : %s\n\n",LLS_Top(stack)->data);

    // 3개의 노드를 푸쉬
    printf("Push three nodes\n");
    LLS_Push(stack, "BBB");
    LLS_Push(stack, "CCC");
    LLS_Push(stack, "DDD");
    // stack 리스트 top의 데이터를 출력
    printf("top : %s\n\n",LLS_Top(stack)->data);   

    // Pop실행 최상위 노드 제거
    printf("Pop\n");
    LLS_Pop(stack);
    // stack 리스트 top의 데이터를 출력
    printf("top : %s\n\n",LLS_Top(stack)->data);

    // Pop을 두번 실행
    printf("Pop two nodes\n");
    LLS_Pop(stack);
    LLS_Pop(stack);
    // stack 리스트 top의 데이터를 출력
    printf("top : %s\n\n",LLS_Top(stack)->data);
    
    LLS_Destroy(stack);

    return 0;
}