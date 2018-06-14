#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

using namespace std;
#define MAX_SIZE 26

/* QUEUE APIS */
typedef struct _qnode {
    char key[27];
    struct _qnode *next;
} QNode;

typedef struct _queue {
    QNode *front;
    QNode *rear;
    int cnt;
} Queue;

QNode *newNode(char *key) {
    QNode *node = (QNode *)malloc(sizeof(QNode));

    strcpy(node->key, key);
    node->next = NULL;
    return node;
}

Queue *createQueue() {
    Queue *node = (Queue *)malloc(sizeof(Queue));
    node->front = NULL;
    node->rear = NULL;
    node->cnt = 0;
    return node;
}

void enQueue(Queue *q, char *key) {

    QNode *node = newNode(key);

    if (q->rear == NULL) {
        q->rear = q->front = node;
        return;
    }
    q->rear->next = node;
    q->rear = node;
    q->cnt++;
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
    q->cnt--;
    return temp;
}

bool isEmpty(Queue *q) {
    if (q->front == NULL) return true;
    return false;
}

void printQueue(Queue *q) {
    if (q == NULL || q->front == NULL)  {
        cout << "Queue is empty \n";
        return;
    }
    QNode *temp = q->front;
    while(temp != NULL) {
        cout << temp->key << endl;
        temp = temp->next;
    }
    cout << endl;
}

QNode *findInQueue(Queue *q, char *key) {
    if (q == NULL || q->front == NULL)  {
        cout << "Queue is empty \n";
        return NULL;
    }
    QNode *temp = q->front;
    while(temp != NULL) {
        if(strcmp(key, temp->key)) {
            cout << "Found Key: " << key << endl;
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteQueue(Queue *q) { /*
    if (q == NULL || q->front == NULL)  {
        cout << "Queue is empty \n";
        return;
    }
    QNode *temp = q->front;
    while(temp != NULL) {
        FREE(temp);
        temp = temp->next;
    }
    cout << endl; */
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
    int cnt;
} trieNode;
trieNode *root = NULL;

trieNode *newTrie() {
    trieNode *node = (trieNode *)malloc(sizeof(trieNode));
    if(node == NULL) {
        printf("Memory alloc failed \n");
        return NULL;
    }
    for(int i = 0; i < ALPHABETS; i++) {
        node->children[i] = NULL;
    }
    node->isEndOfWord = false;
    node->hyperLink = (Queue *)malloc(sizeof(Queue));
    node->cnt = 0;
    return node;
}

void insertTrie(trieNode *root, const char *key) {
    trieNode *pCrawl = root;
    int len = strlen(key);
    int idx = 0;
    for (int ch = 0; ch < len; ch++) {
        idx = CHAR_TO_INDEX(key[ch]);
        if(pCrawl->children[idx] == NULL) {
            pCrawl->cnt++;
            pCrawl->children[idx] = newTrie();
        }
        pCrawl = pCrawl->children[idx];
    }
    pCrawl->isEndOfWord = true;
}

trieNode *searchTrie(trieNode *root, const char *key) {
    int len = strlen(key);
    trieNode *pCrawl = root;
    int idx = 0;
    if (root == NULL) {
        printf("TRIE Is empty \n");
        return false;
    }
    for (int ch = 0; ch < len; ch++) {
        idx = CHAR_TO_INDEX(key[ch]);
        if (pCrawl->children[idx] == NULL) {
            return false;
        }
        pCrawl = pCrawl->children[idx];
    }
    if(pCrawl != NULL && pCrawl->isEndOfWord) {
        return pCrawl;
    }
    return NULL;
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

void freeTrieChildren(trieNode *node) {
    if(node->isEndOfWord == false) {
        for(int i = 0; i < ALPHABETS; i++) {
            if(node->children[i] != NULL) {
                freeTrieChildren(node->children[i]);
            }
        }
    }
    if(node != NULL) {
        FREE(node);
    }
}

void freeTrie(trieNode *root) {
    freeTrieChildren(root);
    FREE(root);
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

int wordCount(trieNode *root) {
    int result = 0;
    if (root->isEndOfWord) {
        result++;
    }
    for(int i = 0; i < ALPHABETS; i++) {
        if(root->children[i]) {
            result += wordCount(root->children[i]);
        }
    }
    return result;
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
        printf("Number of Words with regex: %s is %d\n", query, wordCount(pCrawl));
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

/*
addUrl(Url) {
	if NOT in search in pageTrie
				add in pageTrie
				add in pageQ
}
*/
// add this Url to page queue if not already present in the page or not crawled yet
void addUrl(char str[MAX_SIZE]) {
    if (searchTrie(pageTrie, str) == NULL) {
        enQueue(pageQ, str);
        insertTrie(pageTrie, str);
    }
}

/*
addHyperLink(parent, child) {
	find parent in pageTrie
		add child in pageTrie node Queue
}
*/
// add child hyperlink to parent page
void addHyperLink(char parent[MAX_SIZE], char child[MAX_SIZE]) {
    trieNode *temp = searchTrie(pageTrie, parent);
    if (temp != NULL) { // found parent in pageTrie
        enQueue(temp->hyperLink, child);
    }
}

/*
crawl() {
	deQueue pageQ
		find URL in pageTrie
			find hyperLInk this TrieNode
				loop hyperlink
					enQueue in pageQ ->> if not Exist // Don't do this
					search hyperlink in pageTrie ->> if not Exist add in pageQ...

	delete URL from pageTrie.
	Insert URL in CrawledTrie.
}
*/
// pop the front most page from page queue and crawl the page
void crawl() {
    QNode *tQNode = deQueue(pageQ);
    printf("Crawl Url: %s", tQNode->key);

    trieNode *tPageTrie = searchTrie(pageTrie, tQNode->key);
    QNode *temp = tPageTrie->hyperLink->front;
    while(temp != NULL) {
        if (findInQueue(pageQ, temp->key) != NULL)  {
            enQueue(pageQ, temp->key);
        }
        temp = temp->next;
    }
    deleteTrie(pageTrie, tQNode->key);
    insertTrie(pageCrawled, tQNode->key);
}

// returns the size of the page queue
int queueSize() {

    return pageQ->cnt;
}

/*
query(url) {
	search URL in crawledTree
		//trieNode-> count return;
}
*/
// returns the number of pages in crawled queue which has str as prefix
int query(char query[MAX_SIZE]) {
    trieNode *pCrawl = pageCrawled;

    int len = strlen(url);
    for(int lvl = 0; lvl < len; lvl++) {
        int idx = CHAR_TO_INDEX(query[lvl]);
        if(pCrawl->children[idx] == NULL) {
            return 0;
        }
        pCrawl = pCrawl->children[idx];
    }
    return pCrawl->cnt;
}

int main()
{
    Init();
    addUrl("google");
    addUrl("facebook");

    addHyperLink("google", "twitter");
    crawl();
    cout << "QueueSize: " << queueSize() << endl;
    query("go");

    cout << "-------- THE END --------" << endl;

    /*
	int t, T;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
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


		cout << "#" << t << " " << points / ansPoints << '\n';

	}

*/
	return 0;
}
