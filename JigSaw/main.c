#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3 //49
#define M 3 //15

#define K 5 //5

enum {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

int puzzleSize, pieceSize, nJunkPieces, TC;

typedef struct _piece {
    int info[M*M + 1];
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
        for (int j = 0; j < M*M; j++) {
            pieces[i].info[j] = -2;
        }
    }

    for (int i = 0; i < N*N+K; i++) {
        nPieceIdx[i].top = -2;
        nPieceIdx[i].bottom = -2;
        nPieceIdx[i].right = -2;
        nPieceIdx[i].left = -2;
    }
}

void InitializePieces() {

}

int isMatch(pieceInfo p1, pieceInfo p2, int dir) {
    switch(dir) {
        case TOP:
            {

            }
            break;
        case RIGHT:
            {

            }
            break;
        case BOTTOM:
            {

            }
            break;
        case LEFT:
            {

            }
    }
    return 1;
}

int findNeighbours() {
    int len = 0;
    for(int i = 0; i < (puzzleSize*puzzleSize + nJunkPieces); i++) {
        for(int j = 0; j < (puzzleSize*puzzleSize + nJunkPieces); j++) {
            len++;
        }
    }
    return len;
}

int main()
{
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
	scanf("%d", &TC);
	scanf("%d", &puzzleSize);
	scanf("%d", &pieceSize);
	scanf("%d", &nJunkPieces);

	printf("%d/%d/%d/%d", TC, puzzleSize, pieceSize, nJunkPieces);
	int val = 0;
	scanf("%d", &val);
	while (val != -10) {
        printf("%d ", val);
        scanf("%d", &val);
	}

    findNeighbours();
    return 0;
}
