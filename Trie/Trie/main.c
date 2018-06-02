#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

#define ALPHABETS 26

typedef struct _trieNode {
    struct _trieNode *children[ALPHABETS];
    int isEndOfWord;
} trieNode;
trieNode *root = NULL;

trieNode *newNode() {
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
    for (int lvl = 0; lvl < len; lvl++) {
        idx = CHAR_TO_INDEX(key[lvl]);
        if(!pCrawl->children[idx]) {
            pCrawl->children[idx] = newNode();
        }
        pCrawl = pCrawl->children[idx];
    }
    pCrawl->isEndOfWord = true;
}

bool searchTrie(trieNode *root, const char *key) {
    int len = strlen(key);
    trieNode *pCrawl = root;
    int idx = 0;

    for (int lvl = 0; lvl < len; lvl++) {
        idx = CHAR_TO_INDEX(key[lvl]);
        if (!pCrawl->children[idx]) {
            return false;
        }
        pCrawl = pCrawl->children[idx];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

int main()
{
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    //char output[][32] = {"Not present in trie", "Present in trie"};

    root = newNode();
    for (int i = 0; i < ARRAY_SIZE(keys); i++) {
        insertTrie(root, keys[i]);
    }
    bool findRes = false;
    findRes = searchTrie(root, "answer
                         ");
    printf ("seacrch: %d", findRes);
    return 0;
}
