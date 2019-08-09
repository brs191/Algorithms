#include <stdio.h>
#include <string.h>

#define MAX_TABLE 10

typedef struct _node {
    char key[7];
    struct _node *prev;
} Node;
Node *hTable[MAX_TABLE];
Node a[10000];
int allocIdx = 0;
Node *myAlloc() {
    return &a[allocIdx++];
}

unsigned long myhash(const char *in) {
    unsigned long hash = 5381;
    int c;
    while( c = *in++) {
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    }
    return hash % MAX_TABLE;
}

void insertW(char *in) {
    unsigned long key = myhash(in);
    Node *p = myAlloc();
    strncpy(p->key, in, 7);
    p->prev = hTable[key];
    hTable[key] = p;
}

void searchW(char *in) {
    unsigned long key = myhash(in);
    for(Node *p = hTable[key]; p != NULL; p = p->prev) {
        if(!strncmp(in, p->key, 6)) {
            printf("found the key %s \n", in);
            return;
        }
    }
    printf("not found the key %s\n", in);
}

void removeW(char *in) {
    unsigned long key = myhash(in);

    Node **d = &hTable[key];
    for(Node *p = hTable[key]; p != NULL; p = p->prev) {
        if(!strncmp(p->key, in, 6)) {
            printf("found match delete %s\n", in);
            *d = p->prev;
        }
        d = &p->prev;
    }
}



int main() {

    insertW("one");
    insertW("two");
    insertW("three");
    searchW("two");
    removeW("two");
    searchW("two");   
    return 0;
}