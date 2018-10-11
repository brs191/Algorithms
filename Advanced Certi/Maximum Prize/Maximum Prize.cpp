// Maximum Prize.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>

using namespace std;

/*
char cards[7];
int cardsLen = 0;
int exchanges = 0;

int getStrLen(char cards[]) {
	int cnt = 0;
	while (*cards != '\0') {
		cards++;
		cnt++;
	}
	return cnt;
}

void swap(int i, int j) {
	char ch = cards[i];
	cards[i] = cards[j];
	cards[j] = ch;
}

int getIntfromStr(char cards[], int len)
{
	int value = 0;

	for (int i = 0; i < len; i++) {
		value = value * 10 + (cards[i] - '0');
	}
	return value;
}


int main(int argc, char** argv)
{
	int test_case;
	int T;


	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{

		// 1. Get the inputs
		cin >> cards;
		cin >> exchanges;

		// 2. Implement my logic
		cardsLen = getStrLen(cards);

		if (exchanges > 5) {
			exchanges = 5;
		}

		int startPos = 0;
		int exchangeCnt = 0;
		while ((exchangeCnt < exchanges) && (startPos < cardsLen)) {
			int maxDigit = 0;
			int maxDigitIdx = startPos;
			while (startPos < cardsLen) {
				int j = startPos;
				while (cards[j] != '\0') {
					if (maxDigit <= cards[j]) {
						maxDigit = cards[j];
						maxDigitIdx = j;
					}
					j++;
				}
				if ((maxDigitIdx != j) && (maxDigitIdx != startPos)) {
					swap(startPos, maxDigitIdx);
					exchangeCnt++;
					startPos++;
					break;;
				}
				startPos++;
				maxDigit = 0;
			}
		}
		// 3. print the output
		cout << "#" << test_case << " " << getIntfromStr(cards, cardsLen) << endl;

		// 4. reset my variables

	}
	return 0;//Your program should return 0 on normal termination.
}
*/

#include <iostream>
#include <stdio.h>

#define MAX_LEN 6

using namespace std;


char str[MAX_LEN + 1];


int get_strlen(char* p) {
	int len = 0;
	while (*p != '\0') {
		len++;
		p++;
	}
	return len;
}

int pow(int a, int n) {
	int result = 1;

	while (n--) {
		result *= a;
	}
	return result;
}

int str2int(char* p) {
	int str_len = get_strlen(p);
	int result = 0;
	for (int i = str_len - 1; i >= 0; i--) {
		result += (*p - '0') * pow(10, i);
		p++;
	}
	return result;
}


int DT[1000000][20];

int solve(char* str, int str_len, int chance) {
	int num = str2int(str);
	if (chance == 0) {
		return num;
	}

	if (DT[num][chance]) {
		return DT[num][chance];
	}

	char temp[MAX_LEN + 1];
	temp[str_len] = 0;

	int max = 0;

	for (int i = 0; i < str_len; i++) {
		for (int j = i + 1; j < str_len; j++) {
			if (i == j) continue;

			for (int k = 0; k < str_len; k++) {
				temp[k] = str[k];
			}
			temp[i] = temp[j];
			temp[j] = str[i];

			int t = solve(temp, str_len, chance - 1);

			if (max < t) {
				max = t;
			}
		}
	}

	DT[num][chance] = max;
	return max;
}


int main(void) {
	int test_case;

	freopen("input.txt", "r", stdin);
	scanf("%d", &test_case);

	for (int C = 1; C <= test_case; C++) {
		int result = 0;
		int chance;

		scanf("%s %d", str, &chance);
		int str_len = get_strlen(str);

		result = solve(str, str_len, chance);


		printf("#%d %d\n", C, result);
	}

	return 0;
}
