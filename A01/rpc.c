#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

const char* ai_choice() {
  int aiChoice;
  srand(time(0));
  do {
    aiChoice = rand() % 4;
  } while (aiChoice == 1);
  switch(aiChoice){
    case 0:
      return "rock";
    case 2:
      return "paper";
    case 3:
      return "scissors";
  }
}

void ai_outcome(char aiMove[], char aiBeats[], char winMessage[], char lossMessage[]) {
  if (strcmp(aiMove, "rock") == 0) {
    strcpy(aiBeats, "scissors");
    strcpy(winMessage, "Rock bashes scissors");
    strcpy(lossMessage, "Paper covers rock");
  } 
  else if (strcmp(aiMove, "paper") == 0) {
    strcpy(aiBeats, "rock");
    strcpy(winMessage, "Paper cover rock");
    strcpy(lossMessage, "Scissors cuts paper");
  }
  else {
    strcpy(aiBeats, "paper");
    strcpy(winMessage, "Scissors cut paper");
    strcpy(lossMessage, "Rock bashes scissors");
  }
}

void play(char move[], int scores[]) {
  char aiMove[9];
  char aiBeats[9];
  char winMessage[21];
  char lossMessage[21];
  strcpy(aiMove, ai_choice());
  printf("AI chose %s", aiMove);
  ai_outcome(aiMove, aiBeats, winMessage, lossMessage);
  if (strcmp(move, "rock") != 0 && strcmp(move, "paper") != 0 && strcmp(move, "scissors") != 0) {
    printf("\nYou entered an invalid choice: %s", move);
  }
  else if (strcmp(aiBeats, move) == 0) {
    scores[0]++;
    printf("\n%s", winMessage);
  }
  else if (strcmp(move, aiMove) == 0) {
    ;
  }
  else {
    scores[1]++;
    printf("\n%s", lossMessage);
  }
  printf("\nAI score: %d, Player score: %d\n", scores[0], scores[1]);
}     

int main() {
  int rounds;
  char move[9];
  int scores[2];
  printf("Welcome to Rock, Paper, Scissors!\nHow many rounds do you want to play? ");
  scanf("%d", &rounds);
  scores[0] = 0;  // AI score
  scores[1] = 0;  // Player score
  for (int i = 1; i <= rounds; i++) { 
    printf("Which do you choose? rock, paper, or scissors? ");
    scanf("%s", &move);
    play(move, scores); 
  }
  if (scores[1] > scores[0]) {
    printf("Player wins!\n");
  }
  else if (scores[1] < scores[0]) {
    printf("Player loses!\n");
  }
  else {
    printf("It's a draw!\n");
  }
  return 0;
}

