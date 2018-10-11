// Password Generation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>

using namespace std;

#define REDUCTION 5
#define PWD_ARRAY 8

int reduceValue[REDUCTION] = { 1, 2, 3, 4, 5 };
int PwdItem[PWD_ARRAY] = {0};

int pwdItemCounter = 0;
int reduceValueCounter = 0;

int getNextPwdItem() {
	return PwdItem[pwdItemCounter % PWD_ARRAY];
}

int getNextreduceValue() {
	return reduceValue[reduceValueCounter % REDUCTION];
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

		// 1. Get Inputs
		int temp = 0;
		cin >> temp;

		for (int i = 0; i < PWD_ARRAY; i++) {
			cin >> PwdItem[i];
		}

		// 2. Implement my logs
		int result = 0;
		while (1) {
			result = getNextPwdItem() - getNextreduceValue();
			if (result > 0) {
				PwdItem[pwdItemCounter % PWD_ARRAY] = result;
				pwdItemCounter++;
				reduceValueCounter++;

			}
			else {
				PwdItem[pwdItemCounter % PWD_ARRAY] = 0;
				pwdItemCounter++;
				break;
			}
		}

		// 3. Print the outpu
		cout << "#" << test_case;
		int count = 0;
		while (count < 8) {
			cout << " " << PwdItem[pwdItemCounter % PWD_ARRAY];
			pwdItemCounter++;
			count++;
		}
		cout << endl;		
		
		// 4. Reset my variables
		pwdItemCounter = 0;
		reduceValueCounter = 0;
	}
	return 0;//Your program should return 0 on normal termination.
}