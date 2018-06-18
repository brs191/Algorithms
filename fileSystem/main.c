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
    struct _trieNode *children[ALPHABETS];
    struct _trieNode *sibling[ALPHABETS];
    int eow;
    int suffixCnt;
} trieNode;

trieNode *root = NULL;

trieNode *newTrieNode() {
    trieNode *node = (trieNode *) malloc(sizeof(trieNode));
    if(node != NULL) {
        for(int i = 0; i < ALPHABETS; i++) {
            node->children[i] = NULL;
        }
        node->eow = 0;
        return node;
    }
    return NULL;
}

void insertWord(trieNode *node, char *word) {
    trieNode *pCrawl = node;
    int len = strlen_c(word);
    for(int i = 0; i < len; i++) {
        int idx = CHAR_TO_INDEX(word[i]);
        pCrawl->suffixCnt++;
        if(!pCrawl->children[idx]) {
            pCrawl->children[idx] = newTrieNode();
        }
        pCrawl = pCrawl->children[idx];
    }
    pCrawl->eow = 1;
}

trieNode *searchWord(trieNode *node, char *word) {
    trieNode *pCrawl = node;
    int len = strlen_c(word);
    for (int i = 0; i < len; i++) {
        int idx = CHAR_TO_INDEX(word[i]);
        if (pCrawl->children[idx] == NULL) {
            return NULL;
        }
        pCrawl = pCrawl->children[idx];
    }
    if (pCrawl != NULL && pCrawl->eow) {
        return pCrawl;
    }
    return NULL;
}

bool hasChildren(trieNode *node) {
    for (int i = 0; i < ALPHABETS; i++) {
        if (node->children[i] != NULL) {
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
                if (!hasChildren(node)) { // if empty node to be deleted;
                    return true;
                }
                return false;
            }
        } else {
            int idx = CHAR_TO_INDEX(word[lvl]);
            if(deleteWordHelper(node->children[idx], word, wlen, lvl+1)) {
                FREE(node->children[idx]);
                node->suffixCnt--;
                return (node->eow == 0 && !hasChildren(node));
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

void mkdir(char *path, char *name) {
    char str[100];
    strcpy_c(str, path);
    char *folderName = strsplit_c(str,"/");
    trieNode *pCrawl = NULL;
    while (folderName != NULL)
    {
        pCrawl = searchWord(root, folderName);
        if (pCrawl == NULL) {
            printf("%s not found\n", folderName);
            return;
        } else {
            printf("%s found\n", folderName);
        }
        folderName = strsplit_c(NULL, "/");
    }
    printf("TheEnd....\n");
}

int main()
{
    char keys[][17] = {"the", "a", "there", "answer", "any", "by", "bye", "their",
                      "hello", "dog", "hell", "cat", "hel", "help", "helps", "helping", "anyways"};

    root = newTrieNode();
    for (int i = 0; i < ARRAY_SIZE(keys); i++) {
        insertWord(root, keys[i]);
    }
    mkdir("hello/dog/shekar", "myFolder");

    return 0;
}
