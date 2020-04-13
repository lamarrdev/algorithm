#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* DLL_List_Init();
Node* CDLL_Node_Init(char* str);
Node* CDLL_findFastRoot(LinkedList* list, int n);
void CDLL_insertLastNode(LinkedList* list, char* str);
void CDLL_insertNodeAt(LinkedList* list, char* str, int n);
void CDLL_removeLastNode(LinkedList* list);
void CDLL_removeNodeAt(LinkedList* list, int n);
void CDLL_searchNodes(LinkedList* list, char* str);
void CDLL_printList(LinkedList* list);
void CDLL_destroyList(LinkedList* list);

LinkedList* CDLL_List_Init() {
    LinkedList* newList;
    newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

Node* CDLL_Node_Init(char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(str)+1);
    strcpy(newNode->data, str);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Node* CDLL_findFastRoot(LinkedList* list, int n) {
    Node* selectNode = list->head;
    int totalNodes = list->size;
    int median = totalNodes >> 1;
    int i;

    if(n <= median) {
        printf("next -> %d\n",n);
        for(i=0;i<n;i++) {
            selectNode = selectNode->next;
        }
    }
    else {
        printf("prev <- %d\n",totalNodes-n);
        for(i=0;i< totalNodes-n; i++) {
            selectNode = selectNode->prev;
        }
    }

    return selectNode;
}

void CDLL_insertLastNode(LinkedList* list, char* str) {
    Node* newNode = CDLL_Node_Init(str);

    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else {
        newNode->prev = list->head->prev;
        newNode->next = list->head;
        list->head->prev->next = newNode;
        list->head->prev = newNode;
    }
    list->size++;
}

void CDLL_insertNodeAt(LinkedList* list, char* str, int n) {
    Node* newNode;
    Node* selectNode = list->head;

    if(list->size == 0 || n < 0 || list->size-1 < n) {
        CDLL_insertLastNode(list, str);
        return;
    }

    newNode = CDLL_Node_Init(str);
    if(n==0) {
        newNode->next = list->head;
        newNode->prev = list->head->prev;
        list->head->prev->next = newNode;
        list->head = newNode;
    }
    else {
        selectNode = CDLL_findFastRoot(list,n);
        newNode->next = selectNode;
        newNode->prev = selectNode->prev;
        selectNode->prev->next = newNode;
        selectNode->prev = newNode;
    }
    list->size++;
}

void CDLL_removeLastNode(LinkedList* list) {
    Node* selectNode = list->head;

    if (list->head == NULL) return;

    if (list->head->next == list->head) {
        list->head = NULL;
    }
    else if(list->head->next == list->head->prev) {
        selectNode = list->head->next;
        list->head->next = list->head;
        list->head->prev = list->head;
    }
    else {
        selectNode = list->head->prev;
        list->head->prev = list->head->prev->prev;
        list->head->prev->next = list->head;
    }
    free(selectNode);
    list->size--;
}

void CDLL_removeNodeAt(LinkedList* list, int n) {
    Node* selectNode = list->head;
    int totalNodes = list->size;

    if(list->head == NULL || n < 0 || totalNodes-1 < n) {
        return;
    }
    if(n==0) {
        selectNode = list->head;
        list->head->next->prev = list->head->prev;
        list->head->prev->next = list->head->next;
        list->head = list->head->next;
    }
    else {
        selectNode = CDLL_findFastRoot(list,n);
        selectNode->prev->next = selectNode->next;
        selectNode->next->prev = selectNode->prev;
    }
    free(selectNode);
    list->size--;
}

void CDLL_searchNodes(LinkedList* list, char* str) {
    int access[100] = {-1};
    int accessCount = 0, nodeN = 0;
    Node* s_prevNode = list->head->prev;
    Node* s_nextNode = list->head;
    int loopCount = list->size%2 ? (list->size>>1)+1 : list->size>>1;

    for(int i=1; i<=loopCount; i++) {
        if(!strcmp(s_nextNode->data,str)) {
            access[accessCount] = nodeN;
            access[accessCount+1] = -1;
            accessCount++;
        }
        if(i == loopCount && list->size%2 == 1) {
            break;
        }
        if(!strcmp(s_prevNode->data,str)) {
            access[accessCount] = list->size - i;
            access[accessCount+1] = -1;
            accessCount++;
        }
        s_prevNode = s_prevNode->prev;
        s_nextNode = s_nextNode->next;
        nodeN++;
    }

    if(access[0] == -1) {
        printf("%s Not Found!\n\n",str);
    }
    else {
        for(int i=0; i<100; i++) {
            if(access[i] == -1) {
                break;
            } else {
                printf("%d ",access[i]);
            }
        }
        printf("\n\n");
    }
}

void CDLL_printList(LinkedList* list) {
    Node *selectNode = list->head;
    int i;
    printf("List = ");

    for(i=0; i<list->size; i++) {
        printf("%s",selectNode->data);
        selectNode = selectNode->next;
        if(i != list->size-1) {
            printf(", ");
        }
    }
    printf(" (Total = %d)\n",list->size);

    printf("\n");
} 

void CDLL_destroyList(LinkedList* list) {
    Node *delNode = list->head;
    
    if(list->head != NULL) {
        list->head->prev->next = NULL;
        
        while(delNode != NULL) {
            delNode->prev = NULL;
            list->head = delNode->next;
            free(delNode);
            delNode = list->head;
        }
    }
    free(list);
}

int main() {
    LinkedList* party;

    party = CDLL_List_Init();
    
    printf("Create the list\n");
    CDLL_printList(party);

    printf("Add two nodes\n");
    CDLL_insertLastNode(party,"Ali");
    CDLL_insertLastNode(party,"Joly");
    CDLL_printList(party);

    printf("Insert Chris node at 1 \n");
    CDLL_insertNodeAt(party,"Chris",1);
    CDLL_printList(party); 

    printf("Insert Ali node at 0 \n");
    CDLL_insertNodeAt(party,"Ali",0);
    CDLL_printList(party); 

    printf("Search Ali\n");
    CDLL_searchNodes(party,"Ali");

    printf("Remove node at 2\n");
    CDLL_removeNodeAt(party,2);
    CDLL_printList(party);

    printf("Remove node at 0\n");
    CDLL_removeNodeAt(party,0);
    CDLL_printList(party);

    printf("Remove the last node\n");
    CDLL_removeLastNode(party);
    CDLL_printList(party);

    CDLL_destroyList(party);

    return 0;
}