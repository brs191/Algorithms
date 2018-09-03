#include <stdio.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

void heapInit(void)
{
	heapSize = 0;
}

int heapPush(int value)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	heap[heapSize] = value; // insert at last position;

	int current = heapSize;
	while (current > 0 && heap[current] < heap[(current - 1) / 2]) // if child is less than parent; swap;
	{
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1; // heapSize is index of array;

	return 1;
}

int heapPop(int *value)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*value = heap[0];
	heapSize = heapSize - 1;

	heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize) //until the last left node
	{
		int child;
		if (current * 2 + 2 == heapSize) //last node has no right child
		{
			child = current * 2 + 1; //idx is left child
		}
		else
		{
			if(heap[current * 2 + 1] < heap[current * 2 + 2]) { // left child < right child
				child = current * 2 + 1;  // idx is left child
			} else {
				child = current * 2 + 2;  // idx is right child
			}
		}

		if (heap[current] < heap[child]) // if parent is less than child; position found.
		{
			break;
		}

		int temp = heap[current]; // swap parent and child
		heap[current] = heap[child]; 
		heap[child] = temp;

		current = child; // current is child; go one level down;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	int T, N;
        freopen("input.txt", "r", stdin);
        setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d", &N);
		
		heapInit();
		
		for (int i = 0; i < N; i++)
		{
			int value;
			scanf("%d", &value);
			heapPush(value);
		}

		printf("#%d ", test_case);

		for (int i = 0; i < N; i++)
		{
			int value;
			heapPop(&value);
			printf("%d ", value);
		}
		printf("\n");
	}
	return 0;
}
