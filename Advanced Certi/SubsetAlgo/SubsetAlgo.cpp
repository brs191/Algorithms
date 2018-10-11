// SubsetAlgo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

using namespace std;


char Arr[] = {'A', 'B', 'C', 'D', 'E', 'Z'};
int cnt = 1;

int main()
{
	int n = sizeof(Arr) / sizeof(Arr[0]);

	for (int i = 0; i < (1 << n); i++) {
		cout << cnt++ << "# ";
		for (int j = 0; j < n; j++) {
			if (i & (1 << j)) {
				cout << (char)Arr[j];
			}
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}

