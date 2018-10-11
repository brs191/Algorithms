// bracketmatching.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>

char stack[1001];
int stackLen = 0;

using namespace std;

void stackPush(char ch) {
	stack[stackLen++] = ch;
}

void stackPop() {
	stack[stackLen--] = '\0';
}

// '()', '[]', '{}', and '<>'
bool isSpecialCharPush(char ch) {
	if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
		return true;
	return false;
}

bool isSpecialCharPop(char ch) {
	if (ch == ')' || ch == ']' || ch == '}' || ch == '>')
		return true;
	return false;
}

bool isSpecialCharMatched(char ch) {
	if ((stack[stackLen - 1] == '[') && (ch == ']'))
		return true;
	else if ((stack[stackLen - 1] == '(') && (ch == ')'))
		return true;
	else if ((stack[stackLen - 1] == '{') && (ch == '}'))
		return true;
	else if ((stack[stackLen - 1] == '<') && (ch == '>'))
		return true;

	return false;
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
	// cin >> T;
	T = 10;

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
		int sentenceLen = 0;
		cin >> sentenceLen;

		char sentence[1001];
		cin >> sentence;

		for (int i = 0; i < sentenceLen; i++) {
			if (isSpecialCharMatched(sentence[i])) {
				stackPop();
			}
			else {
				stackPush(sentence[i]);
			}
		}
		if (stackLen == 0)
			cout << "#" << test_case << " " << 1 << endl;
		else
			cout << "#" << test_case << " " << 0 << endl;

		for (int i = 0; i < 1000; i++) {
			stack[i] = '\0';
		}		
	}
	return 0;//Your program should return 0 on normal termination.
}
