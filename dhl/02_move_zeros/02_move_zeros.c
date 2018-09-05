#include <stdio.h>
#define MAX 101
char arr[MAX] = {0,};

void swap(int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int main() {
    int T, t;
    freopen("input.txt", "r", stdin);
    scanf("%d", &T);
    for (t = 1; t <= T; t++) {
        scanf("%s", arr);
        int zero = 0, i;
        for (i = 0; arr[i] != '\0'; i++) {
            if (arr[i] == '0')
                zero++;
            if (arr[i] != '0' && zero != 0)
                swap(i, i - zero);
        }
        printf("%s\n", arr);
    }
    return 0;
}