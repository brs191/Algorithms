#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

using namespace std;
#define MAX_SIZE 26

#define printf //
//#define cout //
/* Util APIs */

int strlen_c(const char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

void strcpy_c(char *to, const char *from) {
    while (*from != '\0') {
        *to = *from;
        to++; from++;
    }
    *(to++) = '\0';
}

int strcmp_c(const char *s1, const char *s2) {
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}

/* Util APIs */

/* QUEUE APIS */
typedef struct _qnode {
    char key[27];
    struct _qnode *next;
} QNode;

typedef struct _queue {
    QNode *front;
    QNode *rear;
    int qCount;
} Queue;

QNode *newNode(char *key) {
    QNode *node = (QNode *)new QNode;

    strcpy_c(node->key, key);
    node->next = NULL;
    return node;
}

Queue *createQueue() {
    Queue *node = (Queue *)new Queue;
    node->front = NULL;
    node->rear = NULL;
    node->qCount = 0;
    return node;
}

void enQueue(Queue *q, char *key) {

    QNode *node = newNode(key);
    q->qCount++;
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
    q->qCount--;
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
        return;
    }
    QNode *temp = q->front;
    //cout << "Q:: ";
    while(temp != NULL) {
        cout << temp->key << " ";
        temp = temp->next;
    }
    cout << endl;
}

QNode *findInQueue(Queue *q, char *key) {
    if (q == NULL || q->front == NULL)  {
        return NULL;
    }
    QNode *temp = q->front;
    while(temp != NULL) {
        if(strcmp_c(key, temp->key) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
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
    Queue *hyperLink;
    int suffixCnt;
} trieNode;
trieNode *root = NULL;

trieNode *newTrie() {
    trieNode *node = (trieNode *)new trieNode;
    if(node == NULL) {
        //printf("Memory alloc failed \n");
        return NULL;
    }
    for(int i = 0; i < ALPHABETS; i++) {
        node->children[i] = NULL;
    }
    node->isEndOfWord = false;
    node->hyperLink = createQueue();
    node->suffixCnt = 0;
    return node;
}

void insertTrie(trieNode *root, const char *key) {
    trieNode *pCrawl = root;
    int len = strlen_c(key);
    int idx = 0;
    for (int ch = 0; ch < len; ch++) {
        idx = CHAR_TO_INDEX(key[ch]);
        pCrawl->suffixCnt++;
        if(pCrawl->children[idx] == NULL) {
            pCrawl->children[idx] = newTrie();
        }
        pCrawl = pCrawl->children[idx];
    }
    pCrawl->isEndOfWord = true;
}

trieNode *searchTrie(trieNode *root, const char *key) {
    int len = strlen_c(key);
    trieNode *pCrawl = root;
    int idx = 0;
    if (root == NULL) {
        return NULL;
    }
    for (int ch = 0; ch < len; ch++) {
        idx = CHAR_TO_INDEX(key[ch]);
        if (pCrawl->children[idx] == NULL) {
            return NULL;
        }
        pCrawl = pCrawl->children[idx];
    }
    if(pCrawl != NULL && pCrawl->isEndOfWord) {
        return pCrawl;
    }
    return NULL;
}

void printTrie(trieNode *node, char *str, int level) {
    if(node->isEndOfWord) {
        str[level] = '\0';
        cout << str << " ";
        printQueue(node->hyperLink);
    }
    for (int i = 0; i < ALPHABETS; i++) {
        if(node->children[i]) {
            str[level] = i + 'a';
            printTrie(node->children[i], str, level+1);
        }
    }
}

void display(trieNode *node, char *str, int lvl, char *query) {
    if(node->isEndOfWord) {
        str[lvl] = '\0';
        //printf("%s%s\n", query, str);
    }
    for(int i = 0; i < ALPHABETS; i++) {
        if(node->children[i]) {
            str[lvl] = i + 'a';
            display(node->children[i], str, lvl+1, query);
        }
    }
}

/* Trie APIs */

void Init();
void addUrl(char url[MAX_SIZE]);
void addHyperLink(char parent[MAX_SIZE], char child[MAX_SIZE]);
void crawl();
int queueSize();
int query(char url[MAX_SIZE]);
char url[MAX_SIZE], parent[MAX_SIZE], child[MAX_SIZE];

Queue *pageQ = NULL;
trieNode *pageCrawled = NULL;
trieNode *pageTrie = NULL;
void Init() { // called once before every test case
    pageQ = createQueue();
    pageCrawled = newTrie();
    pageTrie = newTrie();
}

// add this Url to page queue if not already present in the page or not crawled yet
void addUrl(char str[MAX_SIZE]) {
    if (searchTrie(pageTrie, str) == NULL) {
        enQueue(pageQ, str);
        insertTrie(pageTrie, str);
    }
}

// add child hyperlink to parent page
void addHyperLink(char parent[MAX_SIZE], char child[MAX_SIZE]) {
    trieNode *temp = searchTrie(pageTrie, parent);
    if (temp != NULL) { // found parent in pageTrie
        enQueue(temp->hyperLink, child);
    }
}

// pop the front most page from page queue and crawl the page
void crawl() {
    QNode *tQNode = deQueue(pageQ);

    trieNode *tPageTrie = searchTrie(pageTrie, tQNode->key);
    QNode *temp = tPageTrie->hyperLink->front;
    while(temp != NULL) {
        if (searchTrie(pageTrie, temp->key) == NULL)  {
            enQueue(pageQ, temp->key);
            insertTrie(pageTrie, temp->key);
        }
        temp = temp->next;
    }
    //deleteTrie(pageTrie, tQNode->key);
    insertTrie(pageCrawled, tQNode->key);
}

// returns the size of the page queue
int queueSize() {
    return pageQ->qCount;
}

// returns the number of pages in crawled queue which has str as prefix
int query(char query[MAX_SIZE]) {
    trieNode *pCrawl = pageCrawled;

    int len = strlen_c(query);
    for(int lvl = 0; lvl < len; lvl++) {
        int idx = CHAR_TO_INDEX(query[lvl]);
        if(pCrawl->children[idx] == NULL) {
            return 0;
        }
        pCrawl = pCrawl->children[idx];
    }
    return pCrawl->suffixCnt;
}

int main()
{
 	int t, T;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (t = 1; t <= T; t++)
	{
		Init();
		int cmds;
		cin >> cmds;
		int ansPoints, points = 0;
		cin >> ansPoints;

		for (int i = 0; i < cmds; i++)
		{
			int type;
			cin >> type;
			int ansLen, ansPrefixes, len, prefixes;
            char trieName[27];
			switch (type)
			{
			case 1:
				cin >> url;
				addUrl(url);
				break;
			case 2:
				cin >> parent >> child;
				addHyperLink(parent, child);
				break;
			case 3:

				crawl();
				break;
			case 4:
				len = queueSize();
				cin >> ansLen;
				if (ansLen == len)
					points++;
				break;
			case 5:
				cin >> url;
				cin >> ansPrefixes;
				prefixes = query(url);
				if (prefixes == ansPrefixes)
					points++;
				break;
			}
		}
		cout << "#" << t << " " << points / ansPoints << endl;
	}

	return 0;
}
