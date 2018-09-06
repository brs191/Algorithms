#include <stdio.h>
#include <stdlib.h>

//moveZeros in a an array, by maintaining the non-zeros sequence.
int main()
{
    int arr[] = {0, 2, 0, 0, 0, 0, 0, 0, 0, 0};
    int len = sizeof(arr)/sizeof(arr[0]);

    printf("len is %d\n", len);
    int zIdx = -1;
    for (int i = 0; i < len; i++) {
        if (arr[i] == 0) {
            if (zIdx != -1 && arr[zIdx] == 0)
                continue;
            zIdx = i;
        }
        else if (arr[i] != 0 && zIdx != -1) {
            arr[zIdx] = arr[i];
            arr[i] = 0;
            while (arr[zIdx] != 0 && zIdx < len) zIdx++; // find next zIdx;
        }
    }

    for (int i = 0; i < len; i++) {
        printf ("%d", arr[i]);
    }
    printf("\n");
    return 0;
}
