#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _qnode {
    int key;
    struct _qnode *next;
} QNode;

typedef struct _queue {
    QNode *front;
    QNode *rear;
} Queue;

QNode *newNode(int key) {
    QNode *node = malloc(sizeof(QNode));
    node->key = key;
    node->next = NULL;
    return node;
}

Queue *createQueue() {
    Queue *node = malloc(sizeof(Queue));
    node->front = NULL;
    node->rear = NULL;
    return node;
}

void enQueue(Queue *q, int key) {

    QNode *node = newNode(key);

    if (q->rear == NULL) {
        q->rear = q->front = node;
        return;
    }
    q->rear->next = node;
    q->rear = node;
}

QNode *deQueue(Queue *q) {
    if (q->front == NULL) {
        return NULL;
    }
    QNode *temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

bool isEmpty(Queue *q) {
    if (q->front == NULL) return true;
    return false;
}

void printQueue(Queue *q) {
    if (q == NULL || q->front == NULL)  {
        printf("Queue is empty \n");
        return;
    }
    QNode *temp = q->front;
    while(temp != NULL) {
        printf(" %d ", temp->key);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    printf("Hello world!\n");
    Queue *q = createQueue();
    enQueue(q, 10);
    enQueue(q, 20);
    printQueue(q);
    deQueue(q);
    printQueue(q);
    deQueue(q);
    printQueue(q);

    return 0;
}
