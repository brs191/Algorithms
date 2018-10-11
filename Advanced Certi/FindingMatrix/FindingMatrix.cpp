// FindingMatrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>

using namespace std;

int map[100][100];
int parsedMap[100][100];
int N = 0;

struct _rectangles {
	int i;
	int j;
	int length;
	int breath;
	int area;
};
_rectangles rectangles[100];
int rectNo = 0;

bool findRectangle(int row, int col, int *length, int *breath) {
	if (row >= N || col >= N)
		return false;

	int len = 0, bre = 0;
	// find length in the rectangle.
	for (int j = col; j < N; j++) {
		if (parsedMap[row][j] == 0) {
			break;
		}
		len++;
	}
	if (len > 0) {
		// find breath in the rectangle.
		for (int i = row; i < N; i++) {
			if (parsedMap[i][col] == 0) {
				break;
			}
			bre++;
		}
	}

	*length = len;
	*breath = bre;
	// cout << len << " " << bre << endl;
	if (len > 0 && bre > 0) 
		return true;

	return false;
}

void markParsed(int row, int col, int length, int breath) {

	if (length == 1 && breath == 1) {
		parsedMap[row][col] = -1;
		return;
	}

	for (int i = row; i < row + breath; i++) {
		for (int j = col; j < col + length; j++) {
			parsedMap[i][j] = -1;
		}
	}
	return;
}

void addRectangle(int i, int j, int length, int breath) {
	rectangles[rectNo].i = i;
	rectangles[rectNo].j = j;
	rectangles[rectNo].length = length;
	rectangles[rectNo].breath = breath;
	rectangles[rectNo].area = length * breath;
	rectNo++;
}

void swapRectangles(int i, int j) {
	int temp = 0;
	temp = rectangles[i].i;
	rectangles[i].i = rectangles[j].i;
	rectangles[j].i = temp;

	temp = rectangles[i].j;
	rectangles[i].j = rectangles[j].j;
	rectangles[j].j = temp;

	temp = rectangles[i].length;
	rectangles[i].length = rectangles[j].length;
	rectangles[j].length = temp;

	temp = rectangles[i].breath;
	rectangles[i].breath = rectangles[j].breath;
	rectangles[j].breath = temp;

	temp = rectangles[i].area;
	rectangles[i].area = rectangles[j].area;
	rectangles[j].area = temp;
}

void resetRectangles() {
	for (int i = 0; i < rectNo; i++) {
		rectangles[i].i = 0;
		rectangles[i].j = 0;
		rectangles[i].length = 0;
		rectangles[i].breath = 0;
	}
	rectNo = 0;
}

void resetMaps() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			map[i][j] = parsedMap[i][j] = 0;
		}
	}
}

// print parsed map
void printParsedMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << " " << parsedMap[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void sortRectangles() {
	for (int i = 0; i < rectNo; i++) {
		for (int j = i; j < rectNo; j++) {
			if (rectangles[i].area > rectangles[j].area) {
				swapRectangles(i, j);
			} else if (rectangles[i].area == rectangles[j].area) {
				if (rectangles[i].breath > rectangles[j].breath) {
					swapRectangles(i, j);
				}
			}
		}
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

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Please, implement your algorithm from this section.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////

		// 1. Take Inputs
		cin >> N;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				parsedMap[i][j] = map[i][j];
			}
		}
		// printParsedMap();

		// 2. Implement my logic
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (parsedMap[i][j] != -1 && parsedMap[i][j] != 0) {
					// find a rectangle
					int found = false, length = 0, breath = 0;
					found = findRectangle(i, j, &length, &breath);
					if (found) {
						// mark parsed items
						markParsed(i, j, length, breath);
						// printParsedMap();

						// save rectangle co-ordinates;
						addRectangle(i, j, length, breath);

						// update row;
						// j += length-1; // one ++ from for loop;
					}
				}
			}
		}
	    // printParsedMap();
		// 3. Print output here
		cout << "#" << test_case << ' ' << rectNo;
		sortRectangles();
		for (int i = 0; i < rectNo; i++) {
			cout << ' ' << rectangles[i].breath << ' ' << rectangles[i].length;
		}
		cout << endl;

/*
		for (int i = 0; i < rectNo; i++) {
			cout << rectangles[i].breath << " " << rectangles[i].length << " " << rectangles[i].area << endl;
		}
		sortRectangles();
		cout << endl;
		for (int i = 0; i < rectNo; i++) {
			cout << rectangles[i].breath << " " << rectangles[i].length << " " << rectangles[i].area << endl;
		}
*/
		// 4. Reset the variables
		resetRectangles();
		resetMaps();
	}
	return 0;//Your program should return 0 on normal termination.
}
