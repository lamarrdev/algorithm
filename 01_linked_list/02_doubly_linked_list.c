#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[10];
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    int count;
} LinkedList;


LinkedList* SLL_List_Init();
Node* SLL_Node_Init(LinkedList* list, char* str);
void SLL_insertNodeLast(LinkedList* list, char* str);
void SLL_insertNodeAt(LinkedList* list, char* str, int index);
void SLL_removeNodeLast(LinkedList* list);
void SLL_removeNodeAt(LinkedList* list, int index);
void SLL_searchNodes(LinkedList* list, char* str);
void SLL_printList(LinkedList* list);
void SLL_destroyList(LinkedList* list);


LinkedList* SLL_List_Init() {
    LinkedList* new;
    new = (LinkedList*)malloc(sizeof(LinkedList));
    new->head = NULL;
    new->count = 0;
    return new;
}

Node* SLL_Node_Init(LinkedList* list, char* str) {
    Node* node = (Node*)malloc(sizeof(Node));

    strcpy(node->data, str);
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void SLL_insertAfter(LinkedList* list, char* str) {
    Node* newNode = nodeInit(list,str);
    Node* currentNode;

    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        currentNode = list->head;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }

    list->count++;
}

void SLL_insertMiddle(LinkedList* list, char* str, int index) {
    Node* newNode = nodeInit(list,str);
    Node* currentNode = list->head;
    int count = list->count;
    int i;

    if(count == 0 || index < 0 || count < index) {
        addLastNode(list, str);
        return;
    }

    if(index == 0) {
        newNode->next = list->head;
        list->head = newNode;
        list->count++;
    }
    else {
        for(i=0;i<count;i++) {
            if(i == index-1) {
                newNode->next = currentNode->next;
                currentNode->next = newNode;
                list->count++;
                return;
            }
            currentNode = currentNode->next;
        }
    }
}

void SLL_deleteLastNode(LinkedList* list) {
    Node* prvNode;
    Node* currentNode;

    if (list->head == NULL) return;

    if (list->head->next == NULL) {
        free(list->head);
    } else {
        prvNode = list->head;
        currentNode = list->head->next;
        while(currentNode->next != NULL) { 
            prvNode = currentNode;
            currentNode = currentNode->next;
        }
        free(currentNode);
        prvNode->next = NULL;
    }

    list->count--;
}

void SLL_deleteNode(LinkedList* list, int index) {
    Node* currentNode = list->head;
    Node *deleteNode;
    int count = list->count;
    int i;

    if (list->head == NULL || index < 0 || count < index) {
        return;
    }

    if (index == 0) {
        list->head = list->head->next;
        free(currentNode);
        list->count--;
        return;
    }


    for(i=0;i<count;i++) {
        if(i == index-1) {
            deleteNode = currentNode->next;
            currentNode->next = currentNode->next->next;
            free(deleteNode);
            list->count--;
            return;
        }
            currentNode = currentNode->next;
    }
}



void searchNodes(LinkedList* list, char* str) {
    int access[100] = {-1};
    int accessCount = 0, nodeIndex = 0;
    Node* currentNode = list->head;
    
    while(currentNode != NULL) {
        if(!strcmp(currentNode->data, str)) {
            access[accessCount] = nodeIndex;
            access[accessCount+1] = -1;
            accessCount++;
        }
        nodeIndex++;
        currentNode = currentNode->next;
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

void printLinkedList(LinkedList* list) {
    Node *currentNode = list->head;
    printf("List = ");

    while(currentNode != NULL) {
        printf("%s",currentNode->data);
        currentNode = currentNode->next;
        if( currentNode != NULL ) {
            printf(", ");
        }
    }
    printf(" (Total = %d)\n",list->count);

    printf("\n");
} 

void destroyLinkedList(LinkedList* list) {
    Node *cNode = list->head;

    while(cNode != NULL) {
        list->head = list->head->next;
        free(cNode);
        cNode = list->head;
    }

    free(list);
}

int main() {
    LinkedList* party;

    party = linkedListInit();
    
    printf("Create the list\n");
    printLinkedList(party);

    printf("Add three nodes\n");
    addLastNode(party,"Ali");
    addLastNode(party,"Brian");
    addLastNode(party,"Chris");
    printLinkedList(party);

    printf("Insert node\n");
    insertNode(party,"Chris",1);
    printLinkedList(party); 

    printf("Search Chris\n");
    searchNodes(party,"Chris");

    printf("Delete Brian\n");
    deleteNode(party,2);
    printLinkedList(party);

    printf("Delete the last node\n");
    deleteLastNode(party);
    printLinkedList(party);

    destroyLinkedList(party);

    return 0;
}