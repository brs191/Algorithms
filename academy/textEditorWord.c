#include <stdio.h>
#include <string.h>

typedef struct _word {
    char w[12];
    int wl;
    int go;
    struct _word *next;
    struct _word *prev;
} Node;
Node a[100];
int allocIdx = 0;
Node *myalloc() {
    return &a[allocIdx++];
}
Node *pTail;
Node *pHead;

void print_node() {
    printf("From Head ~~~ \n");
    for (Node *it = pHead->next; it != pTail; it = it->next) {
        printf("%d ", it->go);
    }
    printf("\n");

    printf("From Tail ~~~ \n");
    for(Node *it = pTail->prev; it != pHead; it = it->prev) {
        printf("%d ", it->go);
    }
    printf("\n");
}

void append() {

}

void prepend() {

}

void add() {
    
}

void remove() {

}

int main () {

    allocIdx = 0;

    pHead = myalloc();
    pTail = myalloc();
    pTail->prev = pHead;
    pHead->next = pTail;

    Node *p;
    for (int i = 0; i < 10; i++) {
        p = myalloc();
        p->go = i;
        p->prev = pTail ->prev;
        pTail->prev = p;

        p->next = p->prev->next;
        p->prev->next = p;
    }

    print_node();

    printf("size of word %d\n", (int) sizeof(a[0]));
    printf("done\n");
}