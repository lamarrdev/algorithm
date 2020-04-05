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
Node* DLL_Node_Init(LinkedList* list, char* str);
Node* DLL_findFastRoot(LinkedList* list, int index);
void DLL_insertLastNode(LinkedList* list, char* str);
void DLL_insertNodeAt(LinkedList* list, char* str, int index);
void DLL_removeLastNode(LinkedList* list);
void DLL_removeNodeAt(LinkedList* list, int index);
void DLL_searchNodes(LinkedList* list, char* str);
void DLL_printList(LinkedList* list);
void DLL_destroyList(LinkedList* list);


LinkedList* DLL_List_Init() {
    LinkedList* new;
    new = (LinkedList*)malloc(sizeof(LinkedList));
    new->head = NULL;
    new->count = 0;
    return new;
}

Node* DLL_Node_Init(LinkedList* list, char* str) {
    Node* node = (Node*)malloc(sizeof(Node));

    strcpy(node->data, str);
    node->prev = NULL;
    node->next = NULL;

    return node;
}

Node* DLL_findFastRoot(LinkedList* list, int index) {
    Node* selectNode = list->head;
    int totalNodes = list->count;
    int basis = totalNodes >> 1; // 비트 연산 나누기 2
    int i;

    if(index <= basis) {
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

void DLL_insertLastNode(LinkedList* list, char* str) {
    Node* newNode = DLL_Node_Init(list,str);

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

void DLL_insertNodeAt(LinkedList* list, char* str, int index) {
    Node* newNode;
    Node* selectNode = list->head;
    int totalNodes = list->count;
    int basis; // 기준
    int i;

    if(totalNodes == 0 || index < 0 || totalNodes < index) {
        DLL_insertLastNode(list, str);
        return;
    }

    newNode = DLL_Node_Init(list,str);

    if(index == 0) {
        newNode->next = list->head;
        newNode->prev = list->head->prev;
        list->head->prev->next = newNode;
        list->head = newNode;
    }
    else {
        selectNode = DLL_findFastRoot(list,index);

        newNode->next = selectNode;
        newNode->prev = selectNode->prev;
        selectNode->prev->next = newNode;
        selectNode->prev = newNode;

    }
    
    list->count++;
}

void DLL_removeLastNode(LinkedList* list) {
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

void DLL_removeNodeAt(LinkedList* list, int index) {
    Node* selectNode = list->head;
    int totalNodes = list->count;
    int basis; // 기준
    int i;

    if(list->head == NULL || index < 0 || totalNodes-1 < index) {
        return;
    }

    if(index == 0) {
        selectNode  = list->head;
        list->head->prev->next = list->head->next;
        list->head->next->prev = list->head->prev;
        list->head = list->head->next;
        free(selectNode);
    }
    else {
        selectNode = DLL_findFastRoot(list,index);

        selectNode->prev->next = selectNode->next;
        selectNode->next->prev = selectNode->prev;
        free(selectNode);
    }

    list->count--;
}

// void DLL_searchNodes(LinkedList* list, char* str) {
//     int access[100] = {-1};
//     int accessCount = 0, nodeIndex = 0;
//     Node* selectNode = list->head;
    
//     while(selectNode != NULL) {
//         if(!strcmp(selectNode->data, str)) {
//             access[accessCount] = nodeIndex;
//             access[accessCount+1] = -1;
//             accessCount++;
//         }
//         nodeIndex++;
//         selectNode = selectNode->next;
//     }

//     if(access[0] == -1) {
//         printf("%s Not Found!\n\n",str);
//     } else {
//         for(int i=0; i<100; i++) {
//             if(access[i] == -1) {
//                 break;
//             } else {
//                 printf("%d ",access[i]);
//             }
//         }
//         printf("\n\n");
//     }
// }

void DLL_printList(LinkedList* list) {
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

void DLL_destroyList(LinkedList* list) {
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

    party = DLL_List_Init();
    
    printf("Create the list\n");
    DLL_printList(party);

    printf("Add three nodes\n");
    // DLL_insertLastNode(party,"Ali");
    // DLL_insertLastNode(party,"Brian");
    // DLL_insertLastNode(party,"Kathy");
    // DLL_insertLastNode(party,"Yui");
    // DLL_insertLastNode(party,"Lina");
    // DLL_insertLastNode(party,"Humba");
    DLL_printList(party);

    printf("Insert node at 2 Chris\n");
    DLL_insertNodeAt(party,"Chris",2);
    DLL_printList(party); 

    printf("Insert node at 5 Jun\n");
    DLL_insertNodeAt(party,"Jun",5);
    DLL_printList(party); 

    // printf("Search Chris\n");
    // DLL_searchNodes(party,"Chris");

    printf("Remove node at 1\n");
    DLL_removeNodeAt(party,1);
    DLL_printList(party);

    printf("Remove node at 4\n");
    DLL_removeNodeAt(party,4);
    DLL_printList(party);

    printf("Reomove the last node\n");
    DLL_removeLastNode(party);
    DLL_printList(party);

    DLL_destroyList(party);

    return 0;
}