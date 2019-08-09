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
        if (path[i] == '/') { // find go/name in all the children
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
    if(rn->prev == NULL) {
        rn->parent->child = rn->next;
        if(rn->next != NULL) 
            rn->next->prev = NULL;
    } else {
        if(rn->next != NULL) {
            rn->next->prev = rn->prev;
        }
        rn->prev->next = rn->next;
    }
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

void cmd_rmdir(char path[PATH_MAXLEN + 1]) {
    Node *p = search(path);
    removeNode(p);
}

int dfs(Node *p) {
    int ret = 1;
    Node *sub = p->child;
    while(sub != NULL) {
        ret += dfs(sub);
        sub = sub->next;
    }
    return ret;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
    Node *p = search(path);
    int ret = dfs(p) - 1;
    return ret;
}

void cmd_mv(char sPath[PATH_MAXLEN + 1], char dPath[PATH_MAXLEN + 1]) {
    Node *sn = search(sPath);
    removeNode(sn);

    Node *p = search(dPath);
    append(sn, p);
}

void dfs_cp(Node *s, Node *d) {
    Node *nn = myAlloc();
    nn->name = s->name;
    nn->child = NULL;
    strcpy(nn->nm, s->nm);
    append(nn, d);

    Node *sib = s->next;
    if(sib != NULL) {
        dfs_cp(sib, d);
    }

    if(s->child != NULL) {
        dfs_cp(s->child, nn);
    }
}

void cmd_cp(char sPath[PATH_MAXLEN + 1], char dPath[PATH_MAXLEN + 1]) {
    Node *on = search(sPath);
    Node *p = search(dPath);

    Node *nn = myAlloc();
    nn->name = on->name;
    strcpy(nn->nm, on->nm);
    nn->child = NULL;

    append(nn, p);
    if(on->child != NULL) {
        dfs_cp(on->child, nn);
    }
}

int main() {
    init(10);

    cmd_mkdir("/", "aa");
    cmd_mkdir("/aa/", "zz");
    cmd_mkdir("/aa/", "yy");

    cmd_mkdir("/", "bb");
    cmd_mkdir("/bb/", "ss");
    cmd_mkdir("/bb/", "tt");

    cmd_mkdir("/", "cc");
    cmd_mkdir("/cc/", "11");
    cmd_mkdir("/cc/", "22");
    cmd_mkdir("/bb/ss/", "99");

    printf("# of subs in /: %d\n", cmd_find("/"));
    printf("# of subs in bb: %d\n", cmd_find("/bb/"));
    return 0;
}