#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HYPERLINKS 100

/* URL APIs */
typedef struct _url {
    char name[30];
    char *hyperLink[HYPERLINKS];
    int cnt;
} Url;

void insertHyperLink(Url *url, char *str) {
    url->hyperLink[url->cnt] = str;
    url->cnt++;
};

void printUrl(Url *url) {
    printf("URL: %s [%d]\n", url->name, url->cnt);
    for (int i = 0; i < url->cnt; i++) {
        printf("\t %s\n", url->hyperLink[i]);
    }
}
/* URL APIs */

/* QUEUE APIS */
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
/* QUEUE APIS */

/* Trie APIs */
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ALPHABETS 26
#define FREE(p) \
    free(p); \
    p = NULL;

typedef struct _trieNode {
    struct _trieNode *children[ALPHABETS];
    int isEndOfWord;
} trieNode;
trieNode *root = NULL;

trieNode *newTrieNode() {
    trieNode *node = malloc(sizeof(trieNode));
    if(node == NULL) {
        printf("Memory alloc failed \n");
        return NULL;
    }
    for(int i = 0; i < ALPHABETS; i++) {
        node->children[i] = NULL;
    }
    node->isEndOfWord = false;
    return node;
}

void insertTrie(trieNode *root, const char *key) {
    trieNode *pCrawl = root;
    int len = strlen(key);
    int idx = 0;
    for (int ch = 0; ch < len; ch++) {
        idx = CHAR_TO_INDEX(key[ch]);
        if(pCrawl->children[idx] == NULL) {
            pCrawl->children[idx] = newTrieNode();
        }
        pCrawl = pCrawl->children[idx];
    }
    pCrawl->isEndOfWord = true;
}

bool searchTrie(trieNode *root, const char *key) {
    int len = strlen(key);
    trieNode *pCrawl = root;
    int idx = 0;

    for (int ch = 0; ch < len; ch++) {
        idx = CHAR_TO_INDEX(key[ch]);
        if (pCrawl->children[idx] == NULL) {
            return false;
        }
        pCrawl = pCrawl->children[idx];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

bool haveChildren(trieNode *node) {
    for (int i = 0; i < ALPHABETS; i++) {
        if (node->children[i] != NULL) {
            return true;
        }
    }
    return false;
}

bool deleteHelper(trieNode *node, char *key, int lvl, int len) {
    if (node) {
        if (lvl == len) {
            if (node->isEndOfWord) {
                node->isEndOfWord = 0;
                if (haveChildren(node) == false) {
                    return true;
                }
                return false;
            }
        } else { // go recursive
            int idx = CHAR_TO_INDEX(key[lvl]);
            if(deleteHelper(node->children[idx], key, lvl+1, len)) {
                printf("deleting char %c \n", idx + 'a');
                FREE(node->children[idx]);
                return ((node->isEndOfWord == false) && (haveChildren(node) == false));
            }
        }
    }
    return false;
}

//http://www.techiedelight.com/trie-implementation-insert-search-delete/
void deleteTrie(trieNode *root, char *key) {
    int len = strlen(key);
    bool resul = false;
    if (len > 0) {
        resul = deleteHelper(root, key, 0, len);
    }
    printf("deleteTrie %s resul: %d\n", key, resul);
}

void display(trieNode *node, char *str, int lvl, char *query) {
    if(node->isEndOfWord) {
        str[lvl] = '\0';
        printf("%s%s\n", query, str);
    }
    for(int i = 0; i < ALPHABETS; i++) {
        if(node->children[i]) {
            str[lvl] = i + 'a';
            display(node->children[i], str, lvl+1, query);
        }
    }
}

void printRegEx(trieNode *root, char *query) {
    trieNode *pCrawl = root;

    int len = strlen(query);
    for(int lvl = 0; lvl < len; lvl++) {
        int idx = CHAR_TO_INDEX(query[lvl]);
        if(pCrawl->children[idx] == NULL) {
            return;
        }
        pCrawl = pCrawl->children[idx];
    }
    bool isWord = false;
    if(pCrawl->isEndOfWord) {
        printf("Prefix is the end of the word\n");
        isWord = true;
    }
    bool isLast = false;
    if(haveChildren(pCrawl) == false) {
        printf("Prefix has no subtree\n");
        isLast = true;
    }
    if (isWord && isLast) {
        printf("Prefix query has no other entries \n");
        return;
    }
    if (isLast == false) {
        int level = 0;
        char prefix[1000];
        display(pCrawl, prefix, level, query);
    }
}
/* Trie APIs */

/* Problem APIs */
#define MAX_SIZE 26
void Init() { // called once before every test case

}

// add this Url to page queue if not already present in the page or not crawled yet
void addUrl(char str[MAX_SIZE]) {

}

// add child hyperlink to parent page
void addHyperLink(char parent[MAX_SIZE], char child[MAX_SIZE]) {

}

// pop the front most page from page queue and crawl the page
void crawl() {

}

// returns the size of the page queue
int queueSize() {

    return -1;
}

// returns the number of pages in crawled queue which has str as prefix
int query() {

    return -1;
}

/* Problem APIs */
int main()
{
    Url link;
    strcpy(link.name, "Raja");
    link.cnt = 0;

    insertHyperLink(&link,"google");
    insertHyperLink(&link, "facebook");
    insertHyperLink(&link, "twitter");

    printUrl(&link);

    Queue *q = createQueue();
    enQueue(q, 10);
    enQueue(q, 20);
    printQueue(q);
    deQueue(q);
    printQueue(q);
    deQueue(q);
    printQueue(q);

    char keys[][17] = {"the", "a", "there", "answer", "any", "by", "bye", "their",
                      "hello", "dog", "hell", "cat", "hel", "help", "helps", "helping", "anyways"};

    char output[][32] = {"Not present in trie", "Present in trie"};

    root = newTrieNode();
    for (int i = 0; i < ARRAY_SIZE(keys); i++) {
        insertTrie(root, keys[i]);
    }
    bool findRes = false;
    findRes = searchTrie(root, "answer");
    printf ("seacrch: answer %s\n", output[findRes]);

    deleteTrie(root, "aws");

    findRes = searchTrie(root, "aws");
    printf ("seacrch: aws %s\n", output[findRes]);

    printf("regExpressions for hel::::: \n");
    printRegEx(root, "hel");
    return 0;
}
