#include <stdio.h>
#include <string.h>

#define MAX 100
#define DIGIT(a) (a - '0')

char num1[MAX+1];
char num2[MAX+1];
char sum[MAX+1];

void add() {
  printf("\nadd: %s, %s \n", num1, num2);
  int len1 = strlen(num1);
  int len2 = strlen(num2);
  printf("%d, %d \n", len1, len2);

  int extra = 0;

  int len = 0;
  int slen = 0;

  
  if (len1 > len2) { slen = len1;}
  else { slen = len2; }

  len = slen;
  slen++; // increase for extra
  int j = slen;
  sum[j] = '\0'; j--;
  for(int i = len-1; i >= 0; i--) {
    sum[j] = 0;
    if (len1 > 0) {
      sum[j] += DIGIT(num1[len1-1]);
    }
    if ( len2 > 0) {
      sum[j] += DIGIT(num2[len2-1]);
    }
    sum[j] += extra;

    if (sum[j] > 9) {extra = 1; sum[j] -= 10;}
    else extra = 0;
    printf("extra is %d, %d\n", extra, sum[j]);
    len1--;
    len2--;
    j--;
  }
  if(extra == 1) sum[j] = 1;
  else sum[j] = 0;

  printf("add result is ");
  for (int i = 0; i < slen ; i++) printf("%d", sum[i]);
  printf("\n");
}

int main() {

  int N, T;
  freopen("input.txt", "r", stdin);
  scanf("%d", &T);

  for(int t = 0; t < T; t++) {
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
       int ch = -1, idx = 0;
       printf("skip: %d \n", getchar());

       while((ch = getchar()) != '\n') {
//         printf("[%d] %d ", idx, ch - '0');
         num1[idx] = ch;
         idx++;
       }
       num1[idx] = '\0';

       ch = -1, idx = 0;
       while((ch = getchar()) != '\n') {
         num2[idx] = ch;
         idx++;
       }
       num2[idx] = '\0';

       add();
    }


  }

  return 0;
}
