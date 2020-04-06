#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[10];
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} LinkedList;


LinkedList* DLL_List_Init();
Node* CDLL_Node_Init(LinkedList* list, char* str);
Node* CDLL_findFastRoot(LinkedList* list, int index);
void CDLL_insertLastNode(LinkedList* list, char* str);
void CDLL_insertNodeAt(LinkedList* list, char* str, int index);
void CDLL_removeLastNode(LinkedList* list);
void CDLL_removeNodeAt(LinkedList* list, int index);
void CDLL_searchNodes(LinkedList* list, char* str);
void CDLL_printList(LinkedList* list);
void CDLL_destroyList(LinkedList* list);


LinkedList* CDLL_List_Init() {
    LinkedList* new;
    new = (LinkedList*)malloc(sizeof(LinkedList));
    new->head = NULL;
    new->count = 0;
    return new;
}

Node* CDLL_Node_Init(LinkedList* list, char* str) {
    Node* node = (Node*)malloc(sizeof(Node));

    strcpy(node->data, str);
    node->prev = NULL;
    node->next = NULL;

    return node;
}

Node* CDLL_findFastRoot(LinkedList* list, int index) {
    Node* selectNode = list->head;
    int totalNodes = list->count;
    int median = totalNodes >> 1; // 비트 연산 나누기 2
    int i;

    if(index <= median) {
        printf("next -> %d\n",index);
        for(i=0;i<index;i++) {
            selectNode = selectNode->next;
        }
    }
    else {
        printf("prev <- %d\n",totalNodes-index);
        for(i=0;i< totalNodes-index; i++) {
            selectNode = selectNode->prev;
        }
    }

    return selectNode;
}

void CDLL_insertLastNode(LinkedList* list, char* str) {
    Node* newNode = CDLL_Node_Init(list,str);

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

    list->count++;
}

void CDLL_insertNodeAt(LinkedList* list, char* str, int index) {
    Node* newNode;
    Node* selectNode = list->head;
    int totalNodes = list->count;
    int median; // 중앙값
    int i;

    if(totalNodes == 0 || index < 0 || totalNodes < index) {
        CDLL_insertLastNode(list, str);
        return;
    }

    newNode = CDLL_Node_Init(list,str);

    if(index != 0) {
        selectNode = CDLL_findFastRoot(list,index);
    }

    newNode->next = selectNode;
    newNode->prev = selectNode->prev;
    selectNode->prev->next = newNode;
    selectNode->prev = newNode;
    list->count++;
}

void CDLL_removeLastNode(LinkedList* list) {
    Node* prvNode;
    Node* selectNode = list->head;

    if (list->head == NULL) return;

    if (list->head->next == list->head) {
        list->head = NULL;
    }
    else if(list->head->next == list->head->prev) {
        selectNode = list->head->next;
        list->head->next = list->head;
        list->head->prev = list->head;
    } else {
        selectNode = list->head->prev;
        list->head->prev = list->head->prev->prev;
        list->head->prev->next = list->head;
    }
    free(selectNode);
    list->count--;
}

void CDLL_removeNodeAt(LinkedList* list, int index) {
    Node* selectNode = list->head;
    int totalNodes = list->count;
    int median; // 기준
    int i;

    if(list->head == NULL || index < 0 || totalNodes-1 < index) {
        return;
    }

    if(index != 0) {
        selectNode = CDLL_findFastRoot(list,index);
    }

    selectNode->prev->next = selectNode->next;
    selectNode->next->prev = selectNode->prev;
    free(selectNode);
    list->count--;
}

void CDLL_searchNodes(LinkedList* list, char* str) {
    int access[100] = {-1};
    int accessCount = 0, nodeIndex = 0;
    
    Node* s_prevNode = list->head;
    Node* s_nextNode = list->head;
    int i;
    int basis = list->count >> 1;

    for(int i=0; i<basis; i++) {

        if(i==0 || (list->count >> 1 == 0 && i == basis-1)) {
            if(!strcmp(s_nextNode->data,str)) {
                access[accessCount] = nodeIndex;
                access[accessCount+1] = -1;
                accessCount++;
            }
        }
        else {
            if(!strcmp(s_nextNode->data,str)) {
                access[accessCount] = nodeIndex;
                access[accessCount+1] = -1;
                accessCount++;
            } else if(!strcmp(s_prevNode->data,str)) {
                access[accessCount] = list->count - i;
                access[accessCount+1] = -1;
                accessCount++;
            }            
        }

        s_prevNode = s_prevNode->prev;
        s_nextNode = s_nextNode->next;
        nodeIndex++;
    }


    if(access[0] == -1) {
        printf("%s Not Found!\n\n",str);
    } else {
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
    int tailCheck = 0;
    int i;
    printf("List = ");


    while(tailCheck < list->count) {
        printf("%s",selectNode->data);
        selectNode = selectNode->next;
        tailCheck++;
        if( tailCheck != list->count ) {
            printf(", ");
        }
    }
    printf(" (Total = %d)\n",list->count);

    printf("\n");
} 

void CDLL_destroyList(LinkedList* list) {
    Node *del = list->head;
    
    if(list->head != NULL) {
        list->head->prev->next = NULL;
        
        while(del != NULL) {
            del->prev = NULL;
            list->head = del->next;
            free(del);
            del = list->head;
        }
    }
    free(list);
}

int main() {
    LinkedList* party;

    party = CDLL_List_Init();
    
    printf("Create the list\n");
    CDLL_printList(party);

    printf("Add five nodes\n");
    CDLL_insertLastNode(party,"Ali");
    CDLL_insertLastNode(party,"Brian");
    CDLL_insertLastNode(party,"Kathy");
    CDLL_insertLastNode(party,"Ali");
    CDLL_insertLastNode(party,"Lina");
    CDLL_printList(party);

    printf("Insert node at 2 Chris\n");
    CDLL_insertNodeAt(party,"Chris",2);
    CDLL_printList(party); 

    printf("Insert node at 3 Jun\n");
    CDLL_insertNodeAt(party,"Jun",3);
    CDLL_printList(party); 

    printf("Search Ali\n");
    CDLL_searchNodes(party,"Ali");

    printf("Remove node at 1\n");
    CDLL_removeNodeAt(party,1);
    CDLL_printList(party);

    printf("Remove node at 4\n");
    CDLL_removeNodeAt(party,4);
    CDLL_printList(party);

    printf("Reomove the last node\n");
    CDLL_removeLastNode(party);
    CDLL_printList(party);

    CDLL_destroyList(party);

    return 0;
}