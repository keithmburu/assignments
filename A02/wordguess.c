#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLENGTH 63

int main() {
  printf("Welcome to Word Guess!\n\n");
  FILE* wordFile;
  wordFile = fopen("words.txt", "r");
  char lineCountStr[MAXLENGTH];
  int lineCount;
  fgets(lineCountStr, MAXLENGTH+1, wordFile);
  lineCount = atoi(lineCountStr);
  srand(time(0));
  int line = rand() % lineCount;
  char word[MAXLENGTH];
  for (int i = 0; i < line; i++) {
    fgets(word, MAXLENGTH+1, wordFile);
  } 
  fclose(wordFile);
  //printf("%s\n", word);

  char complete[MAXLENGTH];
  complete[0] = word[0];
  char progress[MAXLENGTH] = "_";
  char guess;
  int found;

  for (int i = 0; i < strlen(word) - 2; i++) {
    strcat(progress, " _");
    strcat(complete, " ");
    complete[2*(i+1)] = word[i+1];  
  }
  complete[MAXLENGTH] = '\0';
  for (int i = 1; i != 0; i++) {
    found = 0;
    printf("Turn: %d\n\n", i);
    printf("%s", progress);
    printf("\nGuess a character: ");
    fgets(&guess, 2, stdin);
    while (fgetc(stdin) != '\n');
    for (int j = 0; j < strlen(word); j++) {
      if (word[j] == guess) {
        progress[2*j] = word[j];
        found = 1;
      }
    }
    if (!found) {
      printf("Sorry, %c not found!\n", guess);
    }
    if (strcmp(complete, progress) == 0) {
      printf("\n%s\n", progress);
      printf("You won in %d turns!\n", i);
      break;
    }
  }
  return 0;
}
