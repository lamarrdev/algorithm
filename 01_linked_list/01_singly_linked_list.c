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
void SLL_insertLastNode(LinkedList* list, char* str);
void SLL_insertNodeAt(LinkedList* list, char* str, int index);
void SLL_removeLastNode(LinkedList* list);
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

void SLL_insertLastNode(LinkedList* list, char* str) {
    Node* newNode = SLL_Node_Init(list,str);
    Node* selectNode;

    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        selectNode = list->head;
        while (selectNode->next != NULL) {
            selectNode = selectNode->next;
        }
        selectNode->next = newNode;
    }

    list->count++;
}

void SLL_insertNodeAt(LinkedList* list, char* str, int index) {
    Node* newNode;
    Node* selectNode = list->head;
    int nodeN;

    if(list->count == 0 || index < 0 || list->count-1 < index) {
        SLL_insertLastNode(list, str);
        return;
    }
    
    newNode = SLL_Node_Init(list,str);

    if(index == 0) {
        newNode->next = list->head;
        list->head = newNode;
        list->count++;
    }
    else {
        nodeN = 0;
        while (selectNode->next != NULL) {
            if(nodeN == index-1) {
                newNode->next = selectNode->next;
                selectNode->next = newNode;
                list->count++;
                break;
            }
            nodeN++;
            selectNode = selectNode->next;
        }
    }
}

void SLL_removeLastNode(LinkedList* list) {
    Node* prvNode;
    Node* selectNode;

    if (list->head == NULL) return;

    if (list->head->next == NULL) {
        free(list->head);
    } else {
        prvNode = list->head;
        selectNode = list->head;
        while(selectNode->next != NULL) { 
            prvNode = selectNode;
            selectNode = selectNode->next;
        }
        free(selectNode);
        prvNode->next = NULL;
    }

    list->count--;
}

void SLL_removeNodeAt(LinkedList* list, int index) {
    Node* selectNode = list->head;
    Node *deleteNode;
    int nodeN;

    if (list->head == NULL || index < 0 || list->count-1 < index) {
        return;
    }

    if (index == 0) {
        list->head = list->head->next;
        free(selectNode);
        list->count--;
    } else {
        nodeN = 0;
        while (selectNode->next != NULL) {
            if(nodeN == index-1) {
                deleteNode = selectNode->next;
                selectNode->next = selectNode->next->next;
                free(deleteNode);
                list->count--;
                break;
            }
            nodeN++;
            selectNode = selectNode->next;
        }
    }
}



void SLL_searchNodes(LinkedList* list, char* str) {
    int access[100] = {-1};
    int accessCount = 0, nodeIndex = 0;
    Node* selectNode = list->head;
    
    while(selectNode != NULL) {
        if(!strcmp(selectNode->data, str)) {
            access[accessCount] = nodeIndex;
            access[accessCount+1] = -1;
            accessCount++;
        }
        nodeIndex++;
        selectNode = selectNode->next;
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
    Node *selectNode = list->head;
    printf("List = ");

    while(selectNode != NULL) {
        printf("%s",selectNode->data);
        selectNode = selectNode->next;
        if( selectNode != NULL ) {
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
    SLL_insertLastNode(party,"Ali");
    SLL_insertLastNode(party,"Brian");
    SLL_insertLastNode(party,"Chris");
    SLL_printList(party);

    printf("Insert node at 1\n");
    SLL_insertNodeAt(party,"Chris",1);
    SLL_printList(party); 

    printf("Insert node at 3\n");
    SLL_insertNodeAt(party,"Makiko",3);
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