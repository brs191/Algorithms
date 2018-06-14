#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

using namespace std;
#define MAX_SIZE 26

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

bool deleteHyperLink(Url *url, char *str) {
    for (int i = 0; i < url->cnt; i++) {
        if (strcmp(url->hyperLink[i], str) == 0) {
            url->hyperLink[i] == NULL;
            return true;
        }
    }
    return false;
}

void printUrl(Url *url) {
    printf("URL: %s [%d]\n", url->name, url->cnt);
    for (int i = 0; i < url->cnt; i++) {
        printf("\t %s\n", url->hyperLink[i]);
    }
}
/* URL APIs */

/* QUEUE APIS */
typedef struct _qnode {
    char key[27];
    struct _qnode *next;
} QNode;

typedef struct _queue {
    QNode *front;
    QNode *rear;
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

void deleteQueue(Queue *q) {
    // TODO
}
/* QUEUE APIS */

void Init();
void addUrl(char url[MAX_SIZE]);
void addHyperLink(char parent[MAX_SIZE], char child[MAX_SIZE]);
void crawl();
int queueSize();
int query(char url[MAX_SIZE]);
char url[MAX_SIZE], parent[MAX_SIZE], child[MAX_SIZE];

Queue *q = NULL;
void Init() { // called once before every test case

    q = createQueue();
}

// add this Url to page queue if not already present in the page or not crawled yet
void addUrl(char str[MAX_SIZE]) {
    enQueue(q, str);
    printQueue(q);

}

// add child hyperlink to parent page
void addHyperLink(char parent[MAX_SIZE], char child[MAX_SIZE]) {
    // if parent is in Q, get Node and addHyperLink
    // if parent is not in Q, what to do?
}

// pop the front most page from page queue and crawl the page
void crawl() {

}

// returns the size of the page queue
int queueSize() {

    return -1;
}

// returns the number of pages in crawled queue which has str as prefix
int query(char url[MAX_SIZE]) {

    return -1;
}

int main()
{
    Queue *q = createQueue();

    Init();
    addUrl("google");
    addUrl("facebook");

    addHyperLink("google", "facebook");

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
