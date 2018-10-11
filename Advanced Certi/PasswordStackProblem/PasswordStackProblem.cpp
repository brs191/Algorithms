// PasswordStackProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>

using namespace std;

char pwd[1001] = { -1, };

int stack[1001] = { -1, };
int stackLen = 0;

void stackPush(int value) {
	stack[stackLen++] = value;
}

void stackPop() {
	stack[stackLen--] = -1;
}

void printStack() {
	for (int i = 0; i < stackLen; i++)
		cout << stack[i]-48;
	cout << endl;
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

	freopen("sample_input.txt", "r", stdin);
	cin >> T;

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
		int pwdLen = 0, i = 0;
		cin >> pwdLen;

		for (i = 0; i < pwdLen; i++) {
			cin >> pwd[i];
		}
		pwd[i] = '\0';

		for (i = 0; i < pwdLen; i++) {
			if (pwd[i] == stack[stackLen-1]) {
				stackPop();
			}
			else {
				stackPush(pwd[i]);
			}
		}

		cout << "#" << test_case << " ";
		printStack();

		for (int i = 0; i < stackLen; i++) {
			stack[i] = -1;
		}
		for (int i = 0; i < strlen(pwd); i++) {
			pwd[i] = -1;
		}
		stackLen = 0;
	}
	return 0;//Your program should return 0 on normal termination.
}