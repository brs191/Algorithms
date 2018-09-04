#include <stdio.h>
#define MAX 101
#define MAX_SIZE 110

char str1[MAX] = {0,};
char str2[MAX] = {0,};

typedef struct {
    int stack[MAX_SIZE];
    int top;
} Stack;

Stack stack1, stack2, result;

void stackInit(Stack *stack) {
    stack->top = 0;
    
}

int stackIsEmpty(Stack *stack) {
    if (stack->top == 0)
        return 1;
    return 0;
}

int stackIsFull(Stack *stack) {
    if (stack->top == MAX_SIZE)
        return 1;
    return 0;
}

int stackPush(Stack *stack, int value) {
    if (stackIsFull(stack))
        return 0;
    
    stack->stack[stack->top] = value;
    stack->top++;
    return 1;
}

int stackPop(Stack *stack, int *value) {
    if (stackIsEmpty(stack))
        return 0;

    stack->top--;
    *value = stack->stack[stack->top];
    return 1;
}


int main() {
    int T, t;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (t = 1; t <= T; t++) {
        int N, i, input;
        char c = getchar();
        stackInit(&stack1);
        stackInit(&stack2);
        stackInit(&result);
        while ((c = getchar()) != '\n')
            stackPush(&stack1, (c - '0'));
        while ((c = getchar()) != '\n')
            stackPush(&stack2, (c - '0'));

        int length = stack1.top > stack2.top ? stack1.top : stack2.top;
        int value1, value2, carry = 0;
        while(length--) {
            if (!stackPop(&stack1, &value1))
                value1 = 0;
            if (!stackPop(&stack2, &value2))
                value2 = 0;
            int subres = value1 + value2 + carry;
            if (subres >= 10) {
                subres = subres % 10;
                carry = 1;
            } else {
                carry = 0;
            }
            stackPush(&result, subres);
        }
        if (carry == 1)
           stackPush(&result, 1);
        
        int size = result.top, val;
        while(size--) {
            stackPop(&result, &val);
            printf("%d", val);
        }
    }
	return 0;
}