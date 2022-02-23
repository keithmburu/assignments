/*
binarychar.c
Author: Keith Mburu
2/25/2022
Converts bit string to its ASCII representation
*/
#include <stdio.h>

/*
Exponentiation function
base: number being raised to an exponent
exp: exponent base is being raised to
returns result of exponentiation
*/
int power(int base, int exp) {
  int result = 1;
  for (int i=0; i < exp; i++) {
    //printf("%d\n", result);
    result *= base;
  }
  return result;
}

int main() {
  printf("Enter 8 bits: ");
  char bin[8];
  scanf("%s", bin);
  int dec = 0;
  //converting binary to decimal
  for (int i=0; i < 8; i++) {
    if (bin[i] == '1') {
      dec += power(2, 7-i);
    }
  }
  //char representation of decimal
  char character = dec;
  printf("Your character is: %c\n", character);
  return 0;
}
