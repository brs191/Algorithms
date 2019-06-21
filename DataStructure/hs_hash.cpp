#include <iostream>
#include <string>

using namespace std;

#define MAX_TABLE 10
int arr_idx = 0;

struct NODE {
	char data[7];
	NODE * prev;  
} a[20000];

NODE *myalloc(void)
{
	return &a[arr_idx++];
}

NODE *hTable[MAX_TABLE];

unsigned long myhash(const char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}
	return hash % MAX_TABLE;
}

int main(void)
{
	freopen("hs_hash_input.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);


	//for (int i = 0; i < 100; i++)
	//{
	//	for (int j = 0; j < 6; j++)
	//	cout << (char)(rand() % 26 + 'a');
	//	cout << endl;
	//}
	arr_idx = 0;  
	for (int i = 0; i < MAX_TABLE; i++)
		hTable[i] = nullptr;

	NODE *p;
	int key;
	char in[7];
	int test_case;

	cin >> test_case;
	for (int T = 0; T < test_case; T++)
	{
		cin >> in;  // receive input string
		key = (int)myhash(in); 
		cout << "Add to Hash table " << key << " : " << in << endl;

		p = myalloc();
		strncpy(p->data, in, 7);
		p->prev = hTable[key];
		hTable[key] = p;

		for (int _tKey = 0; _tKey < MAX_TABLE; _tKey++)
		{
			cout << "Hash table( " << _tKey << " ) :";
			for (NODE * pp = hTable[_tKey]; pp != NULL; pp = pp->prev)
			{
				cout << " " << pp->data;
			}
			cout << endl;
		}
		cout << endl << endl;
	}

	char search[7] = "vrvipy";
	cout << "Searching : " << search << endl;

	int k = (int)myhash(search);
	cout << "Hash table key : " << k << endl;

	for (NODE * pp = hTable[k]; pp != NULL; pp = pp->prev)
	{
		if (!strncmp(search, pp->data, 6))
			cout << "FOUND : " << pp->data << endl << endl;
	}

	NODE **del = &hTable[k];
	for (NODE * iter = hTable[k]; iter != nullptr; iter = iter->prev) 
	{
		if (!strncmp(search, iter->data, 6)) {

			cout << "FOUND & DEL : " << iter->data << endl << endl;
			*del = iter->prev;
		}
		del = &iter->prev;
	}

	cout << "Check delete";
	for (NODE *iter = hTable[k]; iter != nullptr; iter = iter->prev)
	{
		if (!strncmp(search, iter->data, 6))
			cout << "FOUND : " << iter->data << endl << endl;
	}
}
