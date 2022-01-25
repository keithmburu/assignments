/*
rpc.c
Author: Keith Mburu
1/28/2022
Implements the game "rock, paper, scissors"
*/

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define MOVELENGTH 9 // maximum length of null-terminated string representing 
                     // a move
#define MESSAGELENGTH 21 // maximum length of null-terminated string 
                         // representing a win or loss message

/*
Picks a number out of {0, 2, 3} pseudorandomly and returns the corresponding 
move
returns: move to be made by AI
*/
const char* ai_choice() {
  int aiChoice;
  srand(time(0)); // different choices each run
  do {
    aiChoice = rand() % 4;
  } while (aiChoice == 1); // pick again
  switch(aiChoice){
    case 0:
      return "rock";
    case 2:
      return "paper";
    case 3:
      return "scissors";
  }
}

/* 
Determines what move the AI can beat, and the outcome when the player plays 
this move (AI wins) or doesn't play it (AI loses)
aiMove: move made by AI
aiBeats: move AI can beat
winMessage: outcome where AI beats player
lossMessage: outcome where AI is beaten by player
*/ 
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

/*
Simulates one round of the game
move: player's action
scores: AI score and player score
*/
void play(char move[], int scores[]) {
  char aiMove[MOVELENGTH];
  char aiBeats[MOVELENGTH];
  char winMessage[MESSAGELENGTH];
  char lossMessage[MESSAGELENGTH];
  strcpy(aiMove, ai_choice());
  printf("AI chose %s", aiMove);
  ai_outcome(aiMove, aiBeats, winMessage, lossMessage);
  if (strcmp(move, "rock") != 0 && strcmp(move, "paper") != 0 && strcmp(move, "scissors") != 0) {
    printf("\nYou entered an invalid choice: %s", move);
  }
  else if (strcmp(aiBeats, move) == 0) { // if player's move is one the AI can beat
    scores[0]++;
    printf("\n%s", winMessage);
  }
  else if (strcmp(move, aiMove) == 0) {  // if both play the same move
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
  char move[MOVELENGTH];
  int scores[2];
  int aiScore = 0;
  int playerScore = 0;
  printf("Welcome to Rock, Paper, Scissors!\nHow many rounds do you want to play? ");
  scanf("%d", &rounds);
  scores[0] = aiScore; 
  scores[1] = playerScore;  
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

