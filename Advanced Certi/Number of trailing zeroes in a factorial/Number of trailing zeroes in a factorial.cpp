// Number of trailing zeroes in a factorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "iostream"

using namespace std;

int T = 1;
long long int n = 0;

int main()
{

	freopen("factIn.txt", "r", stdin);
	cin >> T;
	for (int i = 1; i <= T; i++) {
		cin >> n;

		int multiple = 5;
		int cnt = 0;
		while (multiple <= n) {
			n = n / multiple;
			multiple *= 5;
			cnt++;
		}
		cout << cnt << endl;
	}
    return 0;
}

