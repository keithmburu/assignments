#include <stdio.h>

unsigned int power(unsigned int base, int exp) {
  unsigned int result = 1;
  for (int i=0; i < exp; i++) {
    printf("%d\n", result);
    result *= base;
  }
  return result;
}

int main() {
  printf("Enter 8 bits: ");
  char bin[8];
  scanf("%s", bin);
  unsigned int dec = 0;
  for (int i=0; i < 8; i++) {
    if (bin[i] == '1') {
      dec += power(2, 7-i);
    }
  }
  char character = dec;
  printf("Your character is: %c\n", character);
  return 0;
}
