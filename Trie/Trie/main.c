#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    for (int ch = 0; ch < len; ch++) {
        idx = CHAR_TO_INDEX(key[ch]);
        if(pCrawl->children[idx] == NULL) {
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

int main()
{
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their", "aws"};
    char output[][32] = {"Not present in trie", "Present in trie"};

    root = newNode();
    for (int i = 0; i < ARRAY_SIZE(keys); i++) {
        insertTrie(root, keys[i]);
    }
    bool findRes = false;
    findRes = searchTrie(root, "answer");
    printf ("seacrch: answer %s\n", output[findRes]);

    findRes = searchTrie(root, "aws");
    printf ("seacrch: aws %s\n", output[findRes]);

    findRes = searchTrie(root, "any");
    printf ("seacrch: any %s\n", output[findRes]);

    deleteTrie(root, "aws");
    deleteTrie(root, "any");
    deleteTrie(root, "answer");
    deleteTrie(root, "a");

    findRes = searchTrie(root, "aws");
    printf ("seacrch: aws %s\n", output[findRes]);
    return 0;
}
