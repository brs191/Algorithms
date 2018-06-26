#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3 //49
#define M 3 //15

#define K 1 //5

enum {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

typedef struct _piece {
    int top[M+1];
    int right[M+1];
    int left[M+1];
    int bottom[M+1];
} pieceInfo;
pieceInfo pieces[N*N+K];

typedef struct _neighbourPieceIdx {
    int top;
    int right;
    int bottom;
    int left;
} neighbourPieceIdx;
neighbourPieceIdx nPieceIdx[N*N+K];

void init() {
    for (int i = 0; i < N*N+K; i++) {
        for (int j = 0; j < M; j++) {
            pieces[i].top[j] = -2;
            pieces[i].bottom[j] = -2;
            pieces[i].right[j] = -2;
            pieces[i].left[j] = -2;
        }
    }

    for (int i = 0; i < N*N+K; i++) {
        nPieceIdx[i].top = -2;
        nPieceIdx[i].bottom = -2;
        nPieceIdx[i].right = -2;
        nPieceIdx[i].left = -2;
    }
}

int isMatch(pieceInfo p1, pieceInfo p2, int dir) {
    switch(dir) {
        case TOP:
            {
                for(int i = 0; i < M; i++) {
                    if (p1.top[i] + p2.top[i] != 0) return -1;
                }
            }
            break;
        case RIGHT:
            {
                for(int i = 0; i < M; i++) {
                    if (p1.right[i] + p2.right[i] != 0) return -1;
                }
            }
            break;
        case BOTTOM:
            {
                for(int i = 0; i < M; i++) {
                    if (p1.bottom[i] + p2.bottom[i] != 0) return -1;
                }
            }
            break;
        case LEFT:
            {
                for(int i = 0; i < M; i++) {
                    if (p1.left[i] + p2.left[i] != 0) return -1;
                }
            }
    }
    return 1;
}

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38 , 39, 40, 41, 42, 43, 44, 46, 46, 47, 48, 49, 50 , 51, 52, 53, 54 };

void swap(int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void perm(int offset, int totalElements) {

	if (offset == totalElements) { // teminate condition
            /*
		for (int i = 0; i < totalElements; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n"); */
		return;
	}
	else {
		for (int i = offset; i < totalElements; i++) {
			swap(i, offset);
			perm(offset + 1, totalElements);
			swap(i, offset);
		}
	}

}

int main()
{
    // step 1; create all the neighbours.
	int len = sizeof(arr) / sizeof(arr[0]);
	perm(0, len);
	printf("Hello World \n");
	getchar();
    return 0;
}
