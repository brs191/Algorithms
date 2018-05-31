#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node *left;
    struct _node *right;
} tNode;

tNode *root = NULL;

tNode *newNode(int data) {
    tNode *node = malloc (sizeof (tNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Stack related functions */
void push(tNode** top_ref, tNode *t);
tNode *pop(struct tNode** top_ref);
int isEmpty(struct tNode *top);


void push(tNode **top_ref, tNode *t) {


}

int main()
{
    printf("Hello world!\n");
    root = newNode(10);
    return 0;
}
