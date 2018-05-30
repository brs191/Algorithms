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

void insertNode(node_t **head, node_t *node) {
    node->next = *head;
    *head = node;
}

void appendNode(node_t **head, node_t *node) {
    if (*head == NULL) {
        *head = node;
    } else {
        node_t *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void deleteNode(node_t **head, int nodeVal) {
    if (*head == NULL) {
        printf("Nothing to delete;;\n");
        return;
    } else if ((*head)->data == nodeVal) {
        if ( (*head)->next == NULL) {
            printf("Only One node to remove. and found it\n");
            free(*head);
            *head = NULL;
        } else {
            printf("deleting first node\n");
            node_t *temp = *head;
            *head = (*head)->next;
            free(temp);
        }
        return;
    } else {
        printf("search for the node %d\n", nodeVal);

        node_t *current = *head;
        node_t *prev = *head;

        while (current != NULL && (current->data != nodeVal)) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) {
            printf("couldn't delete the node %d\n", nodeVal);
            return;
        } else {
            prev->next = current->next;
            free(current);
            printf("deleted the node %d\n", nodeVal);
        }
    }
}

void reverseList(node_t **head) {
    node_t *prev = NULL;
    node_t *curr = *head;
    node_t *NEXT = NULL;

    while (curr != NULL) {
        NEXT = curr->next;
        curr->next = prev;
        prev = curr;
        curr = NEXT;
    }
    *head = prev;
}

void deleteList(node_t **head) {
    node_t *prev = *head;
    while (*head != NULL) {
        prev = *head;
        *head = (*head)->next;
        free(prev);
    }
    printf("Deleted all List\n");
}

void printList(node_t *head) {
    if (head == NULL) {
        printf ("Hello Mister.. List is empty\n");
        return;
    }
    node_t *current = head;
    while (current != NULL) {
        printf (" %d", current->data);
        current = current->next;
    }
    printf("\n");
}

void findMiddleNode(node_t *head) {
    node_t *slowPtr = head;
    node_t *fastPtr = head;
    while(fastPtr != NULL && fastPtr->next != NULL) {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
    }
    printf("middle node is %d \n", slowPtr->data);
}

int main()
{
    for (int i = 10; i > 0; i --) {
        insertNode(&HEAD, createNode(i));
    }
    for (int i = 90; i < 100; i++) {
        appendNode(&HEAD, createNode(i));
    }

    printList(HEAD);

    deleteNode(&HEAD, 1);
    printList(HEAD);

    deleteList(&HEAD);
    printList(HEAD);

    return 0;
}
