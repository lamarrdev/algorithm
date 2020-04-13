#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node : 스택에 하나씩 쌓일 데이터를 정의
typedef struct tNode {
    char* data;
    struct tNode* next;
} Node;

// LinkedListStack : 스택 형태의 리스트를 정의
typedef struct tLinkedListStack {
    Node* head; // 리스트의 헤드 노드 주소를 가리킬 포인터
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
    stack->head = NULL;
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
    // 노드의 next포인터를 NULL로 지정
    newNode->next = NULL;
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
    if(list->head == NULL) {
        // 리스트의 head를 새로운 노드로 설정
        list->head = newNode;
    }
    // 리스트(스택)에 노드가 있는 경우
    else {
        oldTop = list->head;
        // 반복문을 통해 마지막(가장 위) 노드까지 이동
        while(oldTop->next != NULL) {
            oldTop = oldTop->next;
        }
        // 마지막 노드의 next를 새로운 노드로 지정
        // 이렇게해서 새로운 노드가 마지막 노드가 된다.
        oldTop->next = newNode;
    }
    // 리스트(스택)의 탑 필드를 새로운 노드로 지정
    list->top = newNode;
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
    // 리스트(스택)에 노드가 단 하나인 경우
    if(currentTop == list->head) {
        // 현재 리스트(스택)의 헤더와 탑을 NULL로 지정
        list->head = NULL;
        list->top = NULL;
    }
    // 리스트(스택)에 노드가 두개 이상 인 경우
    else {
        newTop = list->head;
        // while문으로 현재의 Top 한칸 밑의 노드까지 이동
        while(newTop->next != currentTop) {
            newTop = newTop->next;
        }
        list->top = newTop;
        newTop->next = NULL;
        list->size--;
    }
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
    Node* delNode= list->head;
    while(delNode != NULL) {
        list->head = delNode->next;
        free(delNode->data);
        free(delNode);
        delNode = list->head;
    }
    free(list);
}

// LLS_printList : 리스트(스택)에 있는 모든 노드의 데이터를 표시
void LLS_printList(LinkedListStack* list) {
    Node* printNode = list->head;
    while(printNode != NULL) {
        printf("%s ",printNode->data);
        printNode = printNode->next;
    }
}

int main(void) {
    // stack이라는 리스트를 생성
    LinkedListStack* stack;
    // 함수를 통해 리스트 형태의 스택을 생성
    stack = LLS_Stack_Init();
    
    // 1개의 노드를 푸쉬후 스택을 확인
    printf("Push a node\n");
    LLS_Push(stack, "AAA");
    LLS_printList(stack);
    // stack 리스트 top의 데이터를 출력
    printf("\ntop : %s\n\n",LLS_Top(stack)->data);

    // 3개의 노드를 푸쉬후 스택을 확인
    printf("Push three nodes\n");
    LLS_Push(stack, "BBB");
    LLS_Push(stack, "CCC");
    LLS_Push(stack, "DDD");
    LLS_printList(stack);
    // stack 리스트 top의 데이터를 출력
    printf("\ntop : %s\n\n",LLS_Top(stack)->data);   

    // Pop실행 최상위 노드 제거
    printf("Pop\n");
    LLS_Pop(stack);
    LLS_printList(stack);
    // stack 리스트 top의 데이터를 출력
    printf("\ntop : %s\n\n",LLS_Top(stack)->data);

    // Pop을 2번 실행
    printf("Pop two times\n");
    LLS_Pop(stack);
    LLS_Pop(stack);
    LLS_printList(stack);
    printf("\ntop : %s\n\n",LLS_Top(stack)->data);

    // stack 리스트의 모든 노드를 삭제하고 리스트도 삭제
    printf("Destroy the stack\n");
    LLS_Destroy(stack);

    return 0;
}