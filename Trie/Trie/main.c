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

int main()
{
    char keys[][17] = {"the", "a", "there", "answer", "any", "by", "bye", "their",
                      "hello", "dog", "hell", "cat", "hel", "help", "helps", "helping", "anyways"};

    char output[][32] = {"Not present in trie", "Present in trie"};

    root = newNode();
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

    freeTrie(root);
    findRes = searchTrie(root, "answer");
    printf ("seacrch: answer %s\n", output[findRes]);

    return 0;
}
