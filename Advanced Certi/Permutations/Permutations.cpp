// Permutations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int arr[] = {1, 2, 3};
int permList[1000][1000] = { 0 };
int permIdx = 0;

void swap(int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void perm(int offset, int totalElements) {

	if (offset == totalElements) { // teminate condition
		for (int i = 0; i < totalElements; i++) {
			permList[permIdx][i] = arr[i];
		}
		permIdx++;
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
	int len = sizeof(arr) / sizeof(arr[0]);

	perm(0, len);

	int cnt = 0;
	for (int i = 0; i < permIdx; i++) {
		int j = 0;
		bool flag = true;
		while (permList[i][j] != 0) {
			if (permList[i][j] == j+1) {
				flag = false;
				break;
			}
			j++;
		}
		if (flag)
			cnt++;
	}
	cout << cnt%1000000007 << endl;
	cout << 6 % 1000000007 << endl;
    return 0;
}

