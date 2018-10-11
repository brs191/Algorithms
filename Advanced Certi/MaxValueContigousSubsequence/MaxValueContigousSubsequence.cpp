// MaxValueContigousSubsequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

using namespace std;

int arr[1000] = { -1 };
int sum = 0;
int maxValue = 0;

int max(int a, int b) {

	if (a > b)
		return a;
	return b;
}

int main()
{
	int T = 0;
	int N = 0;

	freopen("input.txt", "r", stdin);

	cin >> T;
	for (int test_case = 0; test_case < T; test_case++) {
		cin >> N;

		for (int j = 0; j < N; j++) {
			cin >> arr[j];
		}

		int localsum = 0;
		for (int i = 0; i < N; i++) {
			int j = i;
			while (j < N - 1) {
				localsum = arr[i];
				for (int l = i; l < j; l++) {
					localsum += arr[l+1];					
				}
				maxValue = max(maxValue, localsum);
				j++;
			}
		}
		cout << maxValue << endl;

		maxValue = 0;
		sum = 0;
	}
	return 0;
}
