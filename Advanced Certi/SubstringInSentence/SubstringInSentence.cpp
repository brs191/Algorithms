// SubstringInSentence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>

char sentence[1001];
char pattern[11];

using namespace std;

bool findPattern(char sentence[], char pattern[], int patternLen) {
	int count = 0;
	while (*sentence != '\0' && *pattern != '\0') {
		if (*sentence++ == *pattern++) {
			count++;
			continue;
		}
		break;
	}
	if (patternLen == count) {
		return true;
	}
	return false;
}

int main(int argc, char** argv)
{
	int test_case;
	int T = 10;
	/*
	The freopen function below opens input.txt in read only mode and
	sets your standard input to work with the opened file.
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/

	freopen("input.txt", "r", stdin);
	// cin >> T;

	/*
	Read each test case from standard input.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Please, implement your algorithm from this section.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		int TCNo = 0, patternLen = 0;
		cin >> TCNo;
		cin >> pattern;
		for (int i = 0; pattern[i] != '\0'; i++) {
			patternLen++;
		}
		cin >> sentence;

		int i = 0, j = 0;
		int patternMatches = 0;
		while (sentence[i] != '\0') {
			if (findPattern(&sentence[i], pattern, patternLen)) {
				patternMatches++;
			}
			i++;
		}
		cout << "#" << test_case << " " << patternMatches << endl;;
	}
	return 0;//Your program should return 0 on normal termination.
}
