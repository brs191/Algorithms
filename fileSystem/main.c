#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABETS 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ARRAY_SIZE(c) (sizeof(c)/sizeof(c[0]))
#define FREE(c) \
    free(c); \
    c = NULL;

int strlen_c(char *str) {
    int len = 0;
    while(*str != '\0') {
        str++;
        len++;
    }
    return len;
}

int strcmp_c(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++; s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

void strcpy_c(char *dest, const char *src) {
    while(*src != '\0') {
        *dest = *src;
        dest++; src++;
    }
    *(dest++) = '\0';
}

char *strsplit_c(char *str, const char *delim) {
    static char *_buffer;
    if(str != NULL) _buffer = str;
    if(_buffer[0] == '\0') return NULL;

    char *ret = _buffer, *b;
    for(b = _buffer; *b != '\0'; b++) {
        for (const char *d = delim; *d != '\0'; d++) {
            if (*b == *d) { // found a delimiter;
                *b = '\0';
                _buffer = b+1;
                return ret;
            }
        }
    }
    if(*b == '\0') {
        _buffer = b;
    }
    return ret;
}

typedef struct _trieNode {
    struct _trieNode *sibling[ALPHABETS];
    struct _trieNode *parent;
    int eow;
    int suffixCnt;
    int fileCnt;
} trieNode;

trieNode *root = NULL;
trieNode *pwd = NULL;

trieNode *newTrieNode() {
    trieNode *node = (trieNode *) malloc(sizeof(trieNode));
    if(node != NULL) {
        for(int i = 0; i < ALPHABETS; i++) {
            node->sibling[i] = NULL;
        }
        node->eow = 0;
        node->suffixCnt = 0;
        node->fileCnt = 0;
        node->parent = NULL;
        return node;
    }
    return NULL;
}

void Init(trieNode **node) {
    *node = newTrieNode();
}

trieNode *insertWord(trieNode *node, char *word) {
    trieNode *pCrawl = node;
    int len = strlen_c(word);
    for(int i = 0; i < len; i++) {
        int idx = CHAR_TO_INDEX(word[i]);
        pCrawl->suffixCnt++;
        if(!pCrawl->sibling[idx]) {
            pCrawl->sibling[idx] = newTrieNode();
        }
        pCrawl = pCrawl->sibling[idx];
    }
    pCrawl->eow = 1;
    pCrawl->parent = pwd;
    return pCrawl;
}

trieNode *searchWord(trieNode *node, char *word) {
    trieNode *pCrawl = node;
    int len = strlen_c(word);
    for (int i = 0; i < len; i++) {
        int idx = CHAR_TO_INDEX(word[i]);
        if (pCrawl->sibling[idx] == NULL) {
            return NULL;
        }
        pCrawl = pCrawl->sibling[idx];
    }
    if (pCrawl != NULL && pCrawl->eow) {
        return pCrawl;
    }
    return NULL;
}

bool hassibling(trieNode *node) {
    for (int i = 0; i < ALPHABETS; i++) {
        if (node->sibling[i] != NULL) {
            return true;
        }
    }
    return false;
}

bool deleteWordHelper(trieNode *node, char *word, int wlen, int lvl) {
    if(node != NULL) {
        if(lvl == wlen) {
            if (node->eow) {
                node->eow = 0;
                if (!hassibling(node)) { // if empty node to be deleted;
                    return true;
                }
                return false;
            }
        } else {
            int idx = CHAR_TO_INDEX(word[lvl]);
            if(deleteWordHelper(node->sibling[idx], word, wlen, lvl+1)) {
                FREE(node->sibling[idx]);
                node->suffixCnt--;
                return (node->eow == 0 && !hassibling(node));
            }
        }
    }
    return false;
}

void deleteWord(trieNode *node, char *word) {
    int len = strlen_c(word);
    if (len > 0) {
        deleteWordHelper(node, word, len, 0);
    }
}

void freeTrieChildren(trieNode *node) {
    if (!node->eow) {
        for(int i = 0; i < ALPHABETS; i++) {
            if(node->sibling[i] != NULL) {
                freeTrieChildren(node->sibling[i]);
            }
        }
    }
    if(node != NULL) {
        FREE(node);
    }
}

void freeTrie(trieNode *node) {
    freeTrieChildren(node);
    FREE(node);
}

void printTrie(trieNode *pCrawl, char *word, int lvl) {
    if (pCrawl->eow) {
        word[lvl] = '\0';
        printf("%s ", word);
        printf ("\n");
    }
    for (int i = 0; i < ALPHABETS; i++) {
        if (pCrawl->sibling[i]) {
            word[lvl] = 'a' + i;
            printTrie(pCrawl->sibling[i], word, lvl+1);
        }
    }
}

int cd(char *name) {
    if (strcmp_c(name, "..") == 0) { // go to
        pwd = pwd->parent;
    } else {
        trieNode *pCrawl = searchWord(pwd, name);
        if (pCrawl == NULL) {
            return -1;
        }
        pwd = pCrawl;
    }
    return 1;
}

void mkdir(char *name) {
    insertWord(pwd, name);
    pwd->fileCnt++;
}

void rmdir(char *name) {
    if(strcmp_c(name, "*") == 0) {
        if(pwd != NULL) {
            trieNode *temp = pwd->parent;
            freeTrie(pwd);
            pwd = temp;
        }
    } else {
        deleteWord(pwd, name);
        pwd->fileCnt--;
    }
}
int findRegEx(trieNode *node, char *query) {
    trieNode *pCrawl = node;
    int len = strlen_c(query);
    for (int lvl = 0; lvl < len-1; lvl++) {
        int idx = CHAR_TO_INDEX(query[lvl]);
        if(pCrawl->sibling[idx] == NULL) {
            return 0;
        }
        pCrawl = pCrawl->sibling[idx];
    }
    return pCrawl->suffixCnt;
}

int ls (char *name) {
    int len = strlen_c(name);
    if(strcmp_c(name, "*") == 0) {
        return pwd->fileCnt;
    } else if(name[len-1] == '*') { //ends ith regex;
        return findRegEx(pwd, name);
    }
    return 0;
}

int main()
{
    char keys[][17] = {"one", "two", "three", "four", "five"};

    //Init(&root);
    root = newTrieNode();
    pwd = root;

    for (int i = 0; i < ARRAY_SIZE(keys); i++) {
        insertWord(root, keys[i]);
    }

    char Words[100];
    printTrie(root, Words, 0);
    printf("\n");

    cd("one");
    mkdir("india");
    mkdir("telangana");
    mkdir("pakistan");
    mkdir("bangladesh");

    printTrie(pwd, Words, 0);
    printf("\n");
/*
    rmdir("*");
    if(pwd != NULL) {
        printTrie(pwd, Words, 0);
    } else {
        printf("dictory is empty \n");
    }
    printf("\n");
*/
    return 0;
}
