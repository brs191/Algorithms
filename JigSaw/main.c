#include <stdio.h>
#include <stdlib.h>


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


int main()
{
    // step 1; create all the neighbours.

    return 0;
}
