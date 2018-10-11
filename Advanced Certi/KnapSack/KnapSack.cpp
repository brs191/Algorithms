// KnapSack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

using namespace std;

int N = 4;
int M = 0;
int WeightLimit = 0;
int KnapSack[4][4];

int max(int a, int b) {
	return (a > b) ? a : b;
}

int findOptimalItems(int WeightLimit, int idx, int benefits[], int weights[], int K[][4]) {
	if (WeightLimit == 0 || idx == 0)
		return 0;

	if (weights[idx-1] > WeightLimit) // skip it
		return findOptimalItems(WeightLimit, idx-1, benefits, weights, K);

	int includeNitems = benefits[idx-1] + findOptimalItems(WeightLimit - weights[idx-1], idx-1, benefits, weights, K);

	int excludeNitems = findOptimalItems(WeightLimit, idx-1, benefits, weights, K);

	return max(includeNitems, excludeNitems);
}

int main()
{
	int val[] = { 3, 7, 2, 9 };
	int wt[] = { 2, 2, 4, 5 };
	int  W = 10;

	int n = sizeof(val) / sizeof(val[0]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			KnapSack[i][j] = -1;
		}
	}
	int maxBenefit = findOptimalItems(W, n, val, wt, KnapSack);
	cout << "Max Weight " << maxBenefit << endl;
    return 0;
}

