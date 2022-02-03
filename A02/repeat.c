/*
repeat.c
Author: Keith Mburu
2/4/2022
Repeating a string input a given number of times
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Concatenates a string with itself a given number of times and prints the output
*/
void repeat(char* word, int count, char* repeated) {
  for (int i = 0; i < count; i++) {
    strcat(repeated, word);
  }
  printf("Your word is %s\n", repeated);
}

int main() {
  char word[32];
  int count;
  printf("Enter a word: ");
  scanf("%s", word); 
  printf("Enter a count: ");
  scanf("%d", &count);
  char* repeated = malloc(strlen(word) * count); // Allocating heap space for 
                                                 // output
  if (repeated == NULL) { // Checking if malloc was successful
    printf("Cannot allocate new string. Exiting...\n");
    exit(1);
  } else {
      repeat(word, count, repeated);
      free(repeated); // Freeing allocated heap space
  }
  return 0;
}
