#include <stdio.h>
#include <stdlib.h>

// Note if you are modifying the HEAD pointer pass **head;

typedef struct _node {
    int data;
    struct _node *next;
} node_t;

node_t *HEAD = NULL;

node_t *createNode(int data) {
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(node_t *node) {
    node->next = HEAD;
    HEAD = node;
}

void appendNode(node_t *node) {
    if (HEAD == NULL) {
        HEAD = node;
    } else {
        node_t *temp = HEAD;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void deleteNode(node_t *node) {
    if (HEAD == NULL) {
        printf("Nothing to delete;;");
        return;
    }
}

void printList(node_t *head) {
    if (head == NULL) {
        printf ("Hello Mister.. List is empty");
        return;
    }
    printf("Hello Ajossi.. Here is the list \n");
    node_t *current = head;
    while (current != NULL) {
        printf (" %d", current->data);
        current = current->next;
    }
}

int main()
{
    printf("Hello world!\n");
    for (int i = 10; i > 0; i --) {
        insertNode(createNode(i));
    }
    for (int i = 90; i < 100; i++) {
        appendNode(createNode(i));
    }

    printList(HEAD);

    return 0;
}
