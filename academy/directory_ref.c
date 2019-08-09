#include <stdio.h>
#include <string.h>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

typedef struct node {
    int name;
    char nm[NAME_MAXLEN + 1];
    struct node *parent;
    struct node *child;
    struct node *prev, *next;
} Node;

Node a[50000];
int allocIdx;
Node *myAlloc() {
    return &a[allocIdx++];
}
Node *root;

// n is max # of dir created including root
void init(int n) {
    allocIdx = 0;
    root = myAlloc();
    root->name = -1;
    root->child = NULL;
}

Node *search(char path[PATH_MAXLEN + 1]) {
    int go = 0;
    Node *p = root;
    for (int i = 1; path[i]; i++) {
        if (path[i] == '/') {
            Node *next = p->child;
            while(next != NULL) {
                if(next->name == go) {
                    p = next;
                    break;
                }
                next = next->next;
            }
            go = 0;
        } else {
            go <<= 5;
            go |= (path[i] - 'a' +1);
        }
    }
    return p;
}

void appendNode(Node *nn, Node *dst) {
    nn->parent = dst;

    if(dst->child != NULL)
        dst->child->prev = nn;
    nn->prev = NULL;
    nn->next = dst->child;

    dst->child = nn;
}

void removeNode(Node *rn) {

}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    Node *p = search(path);
    int go = 0;
    for (int i = 0; name[ i ]; i++) {
        go <<= 5;
        go |= (name[ i ] - 'a' + 1);
    }

    Node *nn = myAlloc();
    nn->name = go;
    strcpy(nn->nm, name);
    nn->child = NULL;
    appendNode(nn, p);
}

int main() {
    init(10);

    cmd_mkdir("/", "aa");
    cmd_mkdir("/", "bb");
    cmd_mkdir("/", "cc");
    cmd_mkdir("/aa/", "zz");
    cmd_mkdir("/aa/", "yy");
    cmd_mkdir("/bb/", "ss");
    cmd_mkdir("/bb/", "tt");
    cmd_mkdir("/cc/", "11");
    cmd_mkdir("/cc/", "22");

    return 0;
}