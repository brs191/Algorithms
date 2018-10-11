// String Explosion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>

using namespace std;

char sentence[1000001];
int sentenceLen = 0;
char pattern[37];
int patternLen = 0;
int matchCount = 0;

void resetSentence() {
	for (int i = 0; i < sentenceLen; i++) {
		sentence[i] = -1;
	}
}

void resetPattern() {
	for (int i = 0; i < patternLen; i++) {
		pattern[i] = -1;
	}
}

bool isMatchPattern(int offset) {
	int count = 0;
	int counter = 0;
	int i = offset, j = 0;
	while (j < patternLen) {
		while (sentence[i] == -1)
			i++;

		if (sentence[i] != pattern[j]) {
			break;
		}
		count++;
		i++;
		j++;
	}
	if (count == patternLen) {
		matchCount++;
		return true;
	}
	return false;
}

void markParsed(int offset) {

	int counter = 0;
	int i = offset;
	while (counter < patternLen) {
		// skip -1
		while (sentence[i] == -1) {
			i++;
		}
		sentence[i++] = -1;
		counter++;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	The freopen function below opens input.txt in read only mode and
	sets your standard input to work with the opened file.
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/

	freopen("input.txt", "r", stdin);
	cin >> T;

	/*
	Read each test case from standard input.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		// 1. Take Inputs from here
		cin >> sentence;
		for (int i = 0; sentence[i] != '\0'; i++) {
			sentenceLen++;
		}
		cin >> pattern;
		for (int i = 0; pattern[i] != '\0'; i++) {
			patternLen++;
		}

		// 2. Implement my logic here
		while (1) {
			matchCount = 0;
			for (int i = 0; i < sentenceLen; i++) {
				if (sentence[i] != -1 && isMatchPattern(i)) {
					markParsed(i);
				}
			}
			if (matchCount == 0)
				break;
		}


		// 3. Print output here
		bool printed = false;
		for (int i = 0; i < sentenceLen; i++) {
			if (sentence[i] != -1) {
				cout << (char)(sentence[i]);
				printed = true;
			}
		}
		if (printed == false)
			cout << "FRULA";
		cout << endl;

		// 4. Reset my variables
		resetSentence();
		resetPattern();
		patternLen = 0;
		sentenceLen = 0;
		matchCount = 0;
	}
	return 0;//Your program should return 0 on normal termination.
}

