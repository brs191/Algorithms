// PermCombi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

char arr[] = "12345";
int idx = 0;

int permute(char arr[], int fixed, int N) {

    if (fixed == N - 1) {
        idx++;
        cout << "#" << idx << " " << arr << endl;
        // cout << arr << endl;
        // copy all into array;;;
        return 0;
    }

    for (int i = fixed; i < N; i++) {
        int temp = arr[i]; arr[i] = arr[fixed]; arr[fixed] = temp;
        permute(arr, fixed + 1, N);
        temp = arr[i]; arr[i] = arr[fixed]; arr[fixed] = temp;
    }
    return 0;
}

int subsets(char arr[]) {
    int cnt = 0;
    int n = strlen(arr);
    for (int i = 0; i < (1 << n); i++) {
        cout << cnt++ << "# ";
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                cout << (char)arr[j];
                // copy item to arr into array;;;
            }
        }
        cout << endl;
    }
    return 0;
}

// index is for temp data; i is for arr
void combi(char arr[], int n, int r, int index, char temp[], int i) {

    if (index == r) {
        idx++;
        cout << "#" << idx << " " << temp << endl;
        // temp is the combi output array
        return;
    }
    if (i >= n) {
        return;
    }
    temp[index] = arr[i];
    // consider include/exclude
    combi(arr, n, r, index+1, temp, i+1);
    // exclude
    combi(arr, n, r, index, temp, i+1);

}

int combinations(char arr[], int n, int r) {
    // char *temp = new char[r+1];
    char temp[100] = { 0 };
    combi(arr, n, r, 0, temp, 0);
    return 0;
}

int main()
{
    int len = sizeof(arr) / sizeof(arr[0]);
    permute(arr, 0, len-1);
    subsets(arr);
    idx = 0;
    combinations(arr, len-1, 4);

    return 0;
}

