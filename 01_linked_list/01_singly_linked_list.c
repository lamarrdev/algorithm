#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[10];
    struct Node* next;
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
    node->next = NULL;

    return node;
}

void SLL_insertNodeLast(LinkedList* list, char* str) {
    Node* newNode = SLL_Node_Init(list,str);
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

void SLL_insertNodeAt(LinkedList* list, char* str, int index) {
    Node* newNode = SLL_Node_Init(list,str);
    Node* currentNode = list->head;
    int count = list->count;
    int i;

    if(count == 0 || index < 0 || count < index) {
        SLL_insertNodeLast(list, str);
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

void SLL_removeNodeLast(LinkedList* list) {
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

void SLL_removeNodeAt(LinkedList* list, int index) {
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



void SLL_searchNodes(LinkedList* list, char* str) {
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

void SLL_printList(LinkedList* list) {
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

void SLL_destroyList(LinkedList* list) {
    Node *del = list->head;

    while(del != NULL) {
        list->head = list->head->next;
        free(del);
        del = list->head;
    }

    free(list);
}

int main() {
    LinkedList* party;

    party = SLL_List_Init();
    
    printf("Create the list\n");
    SLL_printList(party);

    printf("Add three nodes\n");
    SLL_insertNodeLast(party,"Ali");
    SLL_insertNodeLast(party,"Brian");
    SLL_insertNodeLast(party,"Chris");
    SLL_printList(party);

    printf("Insert node at 1\n");
    SLL_insertNodeAt(party,"Chris",1);
    SLL_printList(party); 

    printf("Search Chris\n");
    SLL_searchNodes(party,"Chris");

    printf("Remove node at 2\n");
    SLL_removeNodeAt(party,2);
    SLL_printList(party);

    printf("Delete the last node\n");
    SLL_removeNodeLast(party);
    SLL_printList(party);

    SLL_destroyList(party);

    return 0;
}