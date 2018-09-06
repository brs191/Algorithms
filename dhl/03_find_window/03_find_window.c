#include <stdio.h>
#include <string.h>

#define MAX 101
int pat[MAX] = {0,};
char arr[MAX] = {0,};
int window[MAX][2] = {0,};

int main() {
    int T, t, ch;
    freopen("input.txt", "r", stdin);
    scanf("%d", &T);
    for (t = 1; t <= T; t++) {
        int ch = getchar();
        int b = 1, c = 0, w = MAX;
        while((ch = getchar()) != '\n') {
            pat[ch] = b;
            c += b;
            b *= 2;
        }

        scanf("%s", arr);
        int size = strlen(arr);
        for (int i = 0; i < size; i++) {
            if (pat[arr[i]] != 0)
                window[i][1] = i;
            else
                window[i][1] = -1;

            for (int j = 0; j <= i; j++) {
                if (window[j][1] != -1 && window[j][0] < c) {
                    window[j][0] |= pat[arr[i]];
                    if (window[j][0] == c) {
                        int localLength = i - window[j][1] +1;
                        if (w > localLength)
                            w = localLength;
                    }
                }
            }
        }
        printf("%d", w);
    }
    return 0;
}