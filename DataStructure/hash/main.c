#include <stdio.h>
#include <string.h>

#define MAX_TABLE 10 // 4096
#define MAX_KEY 64
#define MAX_DATA 128

typedef struct _hashTable {
    char key[MAX_KEY + 1];
    char data[MAX_DATA + 1];
} hashTable;
hashTable hTable[MAX_TABLE];

unsigned long hash(const char *str) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

void addToTable(char *k, char *d) {
    unsigned long h = hash(k);
    int step = 1;
    int i = 0;

    while (hTable[h].key[0] != 0) {
        if (strcmp(hTable[h].key, k) == 0) {
            return;
        }
        h = (h+1) % MAX_TABLE;
    }
    strcpy(hTable[h].key, k);
    strcpy(hTable[h].data, d);
}

int find(const char *key, char *data) {
    unsigned long h = hash(key);
    int cnt = MAX_TABLE;

    while(hTable[h].key[0] != 0 && cnt --) {
        if (strcmp(hTable[h].key, key) == 0) {
            strcpy(data, hTable[h].data);
            return 1;
        }
        h = (h+1) % MAX_TABLE;
    }
    return 0;
}

void printTable() {
    printf("\n");
    for (int i = 0; i < MAX_TABLE; i++)     {
        printf("[%s]:[%s] \n", hTable[i].key, hTable[i].data);
    }
}

int main () {
    char k[MAX_KEY+1];
    char d[MAX_DATA+1];
    for(int i = 0; i < 3; i++) {
        printf("Enter key: ");
        scanf("%[^\n]%*c", k);
        printf("Enter data: ");
        scanf("%[^\n]%*c", d);
        addToTable(k, d);
    }

    printTable();
    getchar();
    return 0;
}