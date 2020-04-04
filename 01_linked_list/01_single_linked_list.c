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


LinkedList* linkedListInit();
Node* nodeInit(LinkedList* list, char* str);
void addLastNode(LinkedList* list, char* str);
void insertNode(LinkedList* list, char* str, int index);
void deleteLastNode(LinkedList* list);
void deleteNode(LinkedList* list, int index);
LinkedList* searchNodes(LinkedList* list, char* str);
void printSearchNodes(LinkedList* list, char* str);
void printLinkedList(LinkedList* list);
void freeLinkedList(LinkedList* list);


LinkedList* linkedListInit() {
    LinkedList* new;
    new = (LinkedList*)malloc(sizeof(LinkedList));
    new->head = NULL;
    new->count = 0;
    return new;
}

Node* nodeInit(LinkedList* list, char* str) {
    Node* node = (Node*)malloc(sizeof(Node));

    strcpy(node->data, str);
    node->next = NULL;

    return node;
}

void addLastNode(LinkedList* list, char* str) {
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

void insertNode(LinkedList* list, char* str, int index) {
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

void deleteLastNode(LinkedList* list) {
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

void deleteNode(LinkedList* list, int index) {
    Node* currentNode = list->head;
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
            currentNode->next = currentNode->next->next;
            list->count--;
            return;
        }
            currentNode = currentNode->next;
    }
    
}

LinkedList* searchNodes(LinkedList* list, char* str){
    LinkedList* access = linkedListInit();
    char intToString[100];

    Node* currentNode = list->head;
    int index = 0;

    while(currentNode != NULL) {
        if(!strcmp(currentNode->data,str)) {
            // Integer to String
            sprintf(intToString, "%d", index);
            addLastNode(access,intToString);
        }
        index++;
        currentNode = currentNode->next;
    }

    if(access->head != NULL) {
        return access;
    } else {
        freeLinkedList(access);
        return NULL;
    }
}

void printSearchNodes(LinkedList* list, char* str) {
    LinkedList* result = searchNodes(list,str);

    if(result != NULL) {
        printLinkedList(result);
        freeLinkedList(result);
    } else {
        printf("%s Not Found\n\n",str);
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

void freeLinkedList(LinkedList* list) {
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
    LinkedList* currentNode;

    party = linkedListInit();
    
    printf("Check the list\n");
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
    printSearchNodes(party,"Chris");

    printf("Delete Brian\n");
    deleteNode(party,2);
    printLinkedList(party);  

    printf("Delete the last node\n");
    deleteLastNode(party);
    printLinkedList(party);

    freeLinkedList(party);

    return 0;
}