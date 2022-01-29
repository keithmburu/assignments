#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char* repeated = malloc(strlen(word) * count);
  if (repeated == NULL) {
    printf("Cannot allocate new string. Exiting...\n");
    exit(1);
  } else {
      repeat(word, count, repeated);
      free(repeated);
  }
  return 0;
}
