#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Complete the findDigits function below.
int findDigits(int n) {
  int num = n;
  int cnt = 0;

  while (num > 0) {
    int d = num % 10;
    if (d != 0 && n%d == 0) {
	cnt++;
        printf("%d cnt, %d", cnt, d);
    }
    num = num/10;
    printf("num is %d", num);
  }
  printf("final num is %d", num);
  if (num != 0 && n%num == 0) cnt++;
  return cnt;
}

int main()
{
    int n = 1012;

    int val = findDigits(n);
    printf("Number of digits: %d", val);
    return 0;
}
