#include <inttypes.h>
#include <stdio.h>

void toLowerUnderscore(char *);
void toLower(char *str) {
  while (*str != '\0') {
    if (*str >= 65 && *str <= 90) {
      *str = *str + 32;
    }else if (*str == ' ') {
      *str = '_';
    }
    str++;
  }
}

int main() {
  char str1[] = "d*a41:2dka ASda4?QW;";
  printf("Original: %s\n", str1);
  toLower(str1);
  printf("C: %s\n", str1);
  char str2[] = "d*a41:2dka ASda4?QW;";
  toLowerUnderscore(str2);
  printf("ASM: %s\n", str2);
  return 0;
}
