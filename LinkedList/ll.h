typedef struct _node {
    int data;
    struct node *next;
} node;

void printList(node *head);
