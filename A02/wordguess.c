#include <stdio.h>
#include <string.h>

int main() {
  printf("Welcome to Word Guess!\n\n");
  char word[32] = "disclaimers";
  char progress[32] = "_";
  char guess;
  int found;

  for (int i = 0; i < strlen(word) - 1; i++) {
    strcat(progress, "_");
  }
  progress[strlen(word)] = '\0';
 
  for (int i = 1; i != 0; i++) {
    found = 0;
    printf("Turn: %d\n\n", i);
    printf("%s", progress);
    printf("\nGuess a character: ");
    scanf("%c", &guess);
    for (int j = 0; j < strlen(word); j++) {
      if (word[j] == guess) {
        progress[j] = word[j];
        found = 1;
      }
    }
    if (!found) {
      printf("\nSorry, %c not found!\n", guess);
    }
    if (strcmp(word, progress) == 0) {
      printf("You won in %d turns!", i);
      break;
    }
  }
  return 0;
}
