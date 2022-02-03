/*
wordguess.c
Author: Keith Mburu
2/4/2022
Implements word guessing game 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLENGTH 63 // highest total length of word chars (32) and spaces (31)

/*
Runs the game until the player wins
*/
void play(char* word, char* progress, char* complete) {
  char guess; // player's guess for one character
  int found; // check for guess correctness
  for (int i = 1; i != 0; i++) { // runs until player wins
    found = 0;
    printf("Turn: %d\n\n", i);
    printf("%s", progress);
    printf("\nGuess a character: ");
    fgets(&guess, 2, stdin); // read in ome character from player
    while (fgetc(stdin) != '\n'); // do away with any remaining characters
    for (int j = 0; j < strlen(word); j++) { 
      if (word[j] == guess) { // check if guess is correct and update progress
        progress[2*j] = word[j];
        found = 1;
      }
    }
    if (!found) {
      printf("Sorry, %c not found!\n", guess);
    }
    else if (strcmp(complete, progress) == 0) { // compare progress to end goal
      printf("You won in %d turns!\n", i);
      break; // end loop
    }
  }
}

int main() {
  printf("Welcome to Word Guess!\n\n");
  
  // getting word to be guessed from a file of words
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

  // setting up current progress and end goal
  char progress[MAXLENGTH] = "_";
  char complete[MAXLENGTH] = "";
  complete[0] = word[0];
  for (int i = 0; i < strlen(word) - 2; i++) {
    strcat(progress, " _");
    strcat(complete, " ");
    complete[2*(i+1)] = word[i+1]; 
  }
  complete[(strlen(word)-1)*2] = '\0';
  play(word, progress, complete);
  return 0;
}
