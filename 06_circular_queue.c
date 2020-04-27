#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
} Node;

typedef struct _CircularQueue {
    Node* nodes;
    unsigned long int capacity;
    unsigned long int front;
    unsigned long int rear;
} CircularQueue;


void createCircularQueue(CircularQueue** _queue, unsigned long int _capacity);
int isEmpty(CircularQueue* _queue);
int isFull(CircularQueue* _queue);
void enqueue(CircularQueue* _queue, int data);
int dequeue(CircularQueue* _queue);
void print(CircularQueue* _queue);
void destroyQueue(CircularQueue* _queue);

void createCircularQueue(CircularQueue** _queue, unsigned long int _capacity) {
    (*_queue) = (CircularQueue*)malloc(sizeof(CircularQueue));
    (*_queue)->nodes = (Node*)malloc(sizeof(Node)* (_capacity+1));
    (*_queue)->capacity = _capacity;
    (*_queue)->front = 0;
    (*_queue)->rear = 0;
}

int isEmpty(CircularQueue* _queue) {
    return (_queue->front == _queue->rear);
}

int isFull(CircularQueue* _queue) {
    if(_queue->front < _queue->rear) {
        return (_queue->rear - _queue->front) == _queue->capacity;
    } else {
        return (_queue->rear +1) == _queue->front;
    }
}

void enqueue(CircularQueue* _queue, int data) {
    unsigned long int p = 0;

    if(isFull(_queue)) {
        printf("Queue is full. dequeue first node\n");
        dequeue(_queue);
    }

    if(_queue->rear == _queue->capacity) {
        p = _queue->rear;
        _queue->rear = 0;
    } 
    else {
        p = _queue->rear++;
    }
    printf("add data in nodes[%lu]. Front:%lu　Rear:%lu\n",p,_queue->front,_queue->rear);
    _queue->nodes[p].data = data;
}

int dequeue(CircularQueue* _queue) {
    unsigned long int p = _queue->front;

    if(isEmpty(_queue)) {
        printf("Queue is empty\n");
        return -999;
    }

    if(_queue->front == _queue->capacity) {
        _queue->front = 0;
    } else {
        _queue->front++;
    }
    printf("delete data in nodes[%lu]. Front:%lu　Rear:%lu\n",p,_queue->front,_queue->rear);
    return _queue->nodes[p].data;
}

void print(CircularQueue* _queue) {
    int i = _queue->front;
    printf("* Queue state\n");

    while(i != _queue->rear) {
        printf("%d ",_queue->nodes[i].data);
        i++;
        if(i-1 == _queue->capacity) {
            i = 0;
        }
        
    }
    printf("\n");

}

void destroyQueue(CircularQueue* _queue) {
    free(_queue->nodes);
    free(_queue);
}


int main(void) {
    CircularQueue *Queue;
    unsigned long int queueSize = 3;

    createCircularQueue(&Queue, queueSize);
    printf("Create Queue(size:%lu) : Front:%lu, Rear:%lu\n\n",queueSize,Queue->front, Queue->rear);

    enqueue(Queue, 1);
    enqueue(Queue, 2);
    enqueue(Queue, 3);
    print(Queue);
    printf("\n");

    enqueue(Queue, 4);
    print(Queue);
    printf("\n");

    dequeue(Queue);
    dequeue(Queue);
    print(Queue);
    printf("\n");

    dequeue(Queue);
    dequeue(Queue);

    destroyQueue(Queue);

    return 0;
}