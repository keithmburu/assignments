/*
word.c
Author: Keith Mburu
2/25/2022
Converts 4-letter word to its integer representation
*/
#include <stdio.h>

int main() {
  printf("Enter 4 characters: ");
  char word[4];
  scanf("%s", word);
  unsigned int result = 0x00000000;
  for (int i=3; i != -1; i--) {
    unsigned int hex = word[i]<<8*(3-i);
    printf("Debug: %c = 0x%08X\n", word[i], hex);
    result += hex;
  }
  printf("Your number is: %d (0x%X)\n", result, result);
  return 0;
}
