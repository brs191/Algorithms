#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
typedef struct _node {
    int data;
    struct _node *left;
    struct _node *right;
} tNode;
tNode *root = NULL;

typedef struct _snode {
    tNode *t;
    struct _snode *next;
}sNode;

tNode *newTnode(int data) {
    tNode *node = malloc (sizeof (tNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Stack related functions */
void push(sNode** top_ref, tNode *t);
tNode *pop(sNode** top_ref);
bool isEmpty(sNode *top);

void push(sNode **top_ref, tNode *t) {
    sNode *new_tNode = malloc(sizeof(sNode));

    if (new_tNode == NULL) {
        printf("stack overflow \n");
        return;
    }
    new_tNode->t = t;
    new_tNode->next = (*top_ref);
    (*top_ref) = new_tNode;
}

tNode *pop(sNode **top_ref) {
    tNode *result;
    sNode *top;

    if (*top_ref == NULL) {
        printf ("stack underflow \n");
        return NULL;
    }
    top = *top_ref;
    *top_ref = top->next;
    result = top->t;
    free(top);
    return result;
}

tNode *peek(sNode *top_ref) {
    if (top_ref == NULL) {
        return NULL;
    }
    return top_ref->t;
}

bool isEmpty(sNode *top) {
    return (top == NULL)? true : false;
}

void inOrder(tNode *root) {
    sNode *stk = NULL;
    tNode *curr = root;
    int done = 0;
    printf("Inorder:  ");
    while (!done) {
        if (curr != NULL) {
            push(&stk, curr);
            curr = curr->left;
        } else {
            if ( !isEmpty(stk)) {
                curr = pop(&stk);
                printf ("%d ", curr->data);
                curr = curr->right;
            } else {
                done = 1;
            }
        }
    }
    printf ("\n");
}

void postOrder(tNode *root) {
    if (root == NULL) {
        printf("Hello Mister.. tree is empty;;");
        return;
    }
    printf ("PostOrder: ");
    sNode *stk = NULL;
    do {
        while (root) {
            if (root->right) {
                push(&stk, root->right);
            }
            push(&stk, root);
            root = root->left;
        }
        root = pop(&stk);
        if (root->right && (peek(stk) == root->right)) {
            pop(&stk);
            push(&stk, root);
            root = root->right;
        } else {
            printf("%d ", root->data);
            root = NULL;
        }
    } while (isEmpty(stk) == false);
    printf ("\n");
}

void preOrder(tNode *root) {
    if (root == NULL) {
        printf("Hello Mister.. Tree is empty \n");
        return;
    }

    printf("preOrder: ");
    sNode *stk = NULL;
    push(&stk, root);
    while (isEmpty(stk) == false) {
        tNode *popItem = pop(&stk);
        printf ("%d ", popItem->data);
        if (popItem->right) {
            push(&stk, popItem->right);
        }
        if (popItem->left) {
            push(&stk, popItem->left);
        }
    }
    printf("\n");
}

int main()
{
    printf("Hello world!\n");
    root = newTnode(1);
    root->left = newTnode(2);
    root->right = newTnode(3);
    root->left->left = newTnode(4);
    root->left->right = newTnode(5);
    root->right->left = newTnode(6);
    root->right->right = newTnode(7);

    inOrder(root);
    postOrder(root);
    preOrder(root);
    return 0;
}
