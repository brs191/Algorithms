#include <stdio.h>

#define INDEX(a) (a - 'a')

int map[26];

void printMap() {
  for (int i = 0; i < 26; i++) {
    printf("%c: %d", i+'a', map[i]);
  }
}

int main() {

  char S[] = "rajashekar";
  char T[] = "skr";

  int sLen = sizeof(S)/sizeof(S[0]) - 1;
  int tLen = sizeof(T)/sizeof(T[0]) - 1;

  printf("%s, %s\n", S, T);
  for (int i = 0; i < tLen; i++) {
    printf("%c ", T[i]);
    int idx = INDEX(T[i]);
    map[idx] = 1;
  }
  printf("\n");

  int sIdx = 0;
  for (int i = 0; i < sLen; i++) {
    sIdx = INDEX(S[i]);
  }

  printf ("The End \n");

  return 0;
}
