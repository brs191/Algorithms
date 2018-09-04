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
  
  if (len1 > len2) { slen = len1; len = len2; }
  else { slen = len2; len = len1; }
  
  slen++;
  int j = slen;
  sum[j] = '\0'; j--;
  for(int i = len-1; i >= 0; i--) {
    if (len1 >= 0 && len2 >= 0) {
      sum[j] = DIGIT(num1[len1-1]) + DIGIT(num2[len2-1]) + extra;
    } else if (len1 < 0) {
      sum[j] = DIGIT(num2[len2-1]) + extra;
    } else if ( len2 < 0) {
      sum[j] = DIGIT(num1[len1-1]) + extra;
    }
    if (sum[j] > 9) {extra = 1; sum[j] -= 10;}
    else extra = 0;
    printf("extra is %d, %d\n", extra, sum[j]);
    len1--;
    len2--;
    j--;
  }
  if(extra == 1) sum[j] = 1;
  else sum[j] = 0;

  printf("%d, %d %d \n", len1, len2, j);
  printf("add result is ");
  for (int i = 0; i < slen ; i++) printf("%d", sum[i]);
  printf("\n");
}

int main() {

  int N, T;
  freopen("input.txt", "r", stdin);
  scanf("%d", &T);
  printf("T is %d\n", T);  
  for(int t = 0; t < T; t++) {
    scanf("%d", &N);
    printf("N is %d\n", N);
    for(int i = 0; i < N; i++) {
       int ch = -1, idx = 0;
       printf("skip: %d \n", getchar());

       while((ch = getchar()) != '\n') {
         printf("[%d] %d ", idx, ch - '0');
         num1[idx] = ch;
         idx++;
       }
       num1[idx] = '\0';
       printf("idx: %d\n", idx);
       ch = -1, idx = 0;
       while((ch = getchar()) != '\n') {
         num2[idx] = ch;
         idx++;
       }
       num1[idx] = '\0';

       add();
    }

    
  }

  return 0;
}
/*
int main() {

  while(1) {
    printf("1. For Input Integer\n2. Add\n3. Exit\n");
    int cmd = 0;
    scanf("%d", &cmd);
    switch(cmd) {
      case 2:
      {
	add();
        continue;
      }
      case 1:
      {
        int ch = getch();
        while(ch != EOF) {
          putchar(ch); 
          ch = getch();
        }
        printf("Enter pressed \n");
        continue;
      }
      case 3:
      default:
	break;
    }
  }
  printf("The End\n");
  return 0;
}
*/
