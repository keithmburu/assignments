#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

void play(char move[], int aiScore, int playerScore) {
  char aiMove[8];
  strcpy(aiMove, ai_choice());
  printf("AI chose %s", aiMove);
  if (strcmp(move, aiMove) != 0) { 
    if (strcmp(move, "scissors") == 0){
      if (strcmp(aiMove, "paper") == 0) {
        printf("Scissors cut paper");
        playerScore++;
      } 
    }
    else if (strcmp(move, "paper") == 0) {
      if (strcmp(aiMove, "scissors") == 0) {
        printf("Scissors cut paper");
        aiScore++;
      }
    } 
    else if (strcmp(move, aiMove) < 0) {
      if (strcmp(move, "paper") == 0) {
        printf("Paper covers rock");
      } 
      else {
        printf("Rock bashes scissors");
      }
      playerScore++;
    }
    else if (strcmp(move, aiMove) > 0) {
      if (strcmp(aiMove, "paper") == 0) {
        printf("Paper covers rock");
      } 
      else {
        printf("Rock bashes scissors");
      }
      aiScore++;
    }
  }
  printf("AI score: %d, Player score: %d", aiScore, playerScore);
}     

const char* ai_choice() {
  int aiChoice;
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

int main() {
  //srand(time(0));
  int rounds;
  char move[8];
  int aiScore;
  int playerScore;
  printf("Welcome to Rock, Paper, Scissors!\nHow many rounds do you want to play? ");
  scanf("%d", rounds);
  printf("Which do you choose? rock, paper, or scissors? ");
  scanf("%s", move);
  aiScore = 0;
  playerScore = 0;
  for (int i = 1; i <= rounds; i++) {
    play(move, aiScore, playerScore); 
  }
  return 0;
}

