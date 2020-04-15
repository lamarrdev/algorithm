#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;


LinkedList* SLL_List_Init();
Node* SLL_Node_Init(char* str);
void SLL_insertLastNode(LinkedList* list, char* str);
void SLL_insertNodeAt(LinkedList* list, char* str, int index);
void SLL_removeLastNode(LinkedList* list);
void SLL_removeNodeAt(LinkedList* list, int index);
void SLL_searchNodes(LinkedList* list, char* str);
void SLL_printList(LinkedList* list);
void SLL_destroyList(LinkedList* list);



LinkedList* SLL_List_Init() {
    LinkedList* newList;
    newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->size = 0;

    return newList;
}

Node* SLL_Node_Init(char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(str)+1);
    strcpy(newNode->data, str);
    newNode->next = NULL;

    return newNode;
}

void SLL_insertLastNode(LinkedList* list, char* str) {
    Node* newNode = SLL_Node_Init(str);
    Node* selectNode = list->head;;

    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        while (selectNode->next != NULL) {
            selectNode = selectNode->next;
        }
        selectNode->next = newNode;
    }
    list->size++;
}

void SLL_insertNodeAt(LinkedList* list, char* str, int n) {
    Node* newNode;
    Node* selectNode = list->head;;
    int i;

    if(list->size == 0 || n < 0 || list->size-1 < n) {
        SLL_insertLastNode(list, str);
        return;
    }
    
    newNode = SLL_Node_Init(str);

    if(n == 0) {
        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        for(int i=0; i<n-1; i++){
            selectNode = selectNode->next;
        }
        newNode->next = selectNode->next; 
        selectNode->next = newNode;
    }
    list->size++;
}

void SLL_removeLastNode(LinkedList* list) {
    Node* prvNode;
    Node* selectNode = list->head;;

    if (list->head == NULL) return;

    if (list->head->next == NULL) {
        free(list->head->data);
        free(list->head);
        list->head = NULL;
    }
    else {
        while(selectNode->next != NULL) { 
            prvNode = selectNode;
            selectNode = selectNode->next;
        }
        free(selectNode->data);
        free(selectNode);
        prvNode->next = NULL;
    }
    list->size--;
}

void SLL_removeNodeAt(LinkedList* list, int n) {
    Node* selectNode = list->head;
    Node *deleteNode;
    int i;

    if (list->head == NULL || n < 0 || list->size-1 < n) {
        return;
    }

    if (n == 0) {
        list->head = list->head->next;
        free(selectNode->data);
        free(selectNode);
    }
    else {
        for(int i=0; i<n-1; i++){
            selectNode = selectNode->next;
        }
        deleteNode = selectNode->next;
        selectNode->next = selectNode->next->next;
        free(deleteNode->data);
        free(deleteNode);
    }
    list->size--;
}

void SLL_searchNodes(LinkedList* list, char* str) {
    int access[100] = {-1};
    int accessCount = 0;
    Node* selectNode = list->head;
    int i;
    
    for(i=0; i<list->size; i++) {
        if(!strcmp(selectNode->data, str)) {
            access[accessCount] = i;
            access[accessCount+1] = -1;
            accessCount++;
        }
        selectNode = selectNode->next;
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

void SLL_printList(LinkedList* list) {
    Node *selectNode = list->head;
    printf("List = ");

    while(selectNode != NULL) {
        printf("%s",selectNode->data);
        selectNode = selectNode->next;
        if( selectNode != NULL ) {
            printf(", ");
        }
    }
    printf(" (Total = %d)\n",list->size);
    printf("\n");
} 

void SLL_destroyList(LinkedList* list) {
    Node *delNode = list->head;

    while(delNode != NULL) {
        list->head = list->head->next;
        free(delNode->data);
        free(delNode);
        delNode = list->head;
    }
    free(list);
}

int main() {
    LinkedList* party;

    party = SLL_List_Init();
    
    printf("Create the list\n");
    SLL_printList(party);

    printf("Add three nodes\n");
    SLL_insertLastNode(party,"Ali");
    SLL_insertLastNode(party,"Brian");
    SLL_insertLastNode(party,"Chris");
    SLL_printList(party);

    printf("Insert Chris node at 0\n");
    SLL_insertNodeAt(party,"Chris",0);
    SLL_printList(party); 

    printf("Insert Panda node at 1\n");
    SLL_insertNodeAt(party,"Panda",1);
    SLL_printList(party); 

    printf("Search Chris\n");
    SLL_searchNodes(party,"Chris");

    printf("Remove node at 2\n");
    SLL_removeNodeAt(party,2);
    SLL_printList(party);

    printf("Remove node at 1\n");
    SLL_removeNodeAt(party,1);
    SLL_printList(party);

    printf("Delete the last node\n");
    SLL_removeLastNode(party);
    SLL_printList(party);

    SLL_destroyList(party);

    return 0;
}