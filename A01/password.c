/*
password.c
Author: Keith Mburu
1/28/2022
Convert word to bad password
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 10 // maximum word length

/* 
Converts word given by the user to a bad password
word: input from user
size: length of word
badpassword: output to be constructed
*/
void bad_password(char word[], int size, char badpassword[]) {
  for (int i = 0; i < size; i++) {
    switch(word[i]) { 
      case 'e': // replace
        badpassword[i] = '3';
        break;
      case 'l':
        badpassword[i] = '1';
        break;
      case 'a':
        badpassword[i] = '@';
        break;
      default:  // copy
        badpassword[i] = word[i];
    }
  }
  badpassword[size] = '\0'; // terminate string
}

int main() {
  char word[MAXLENGTH];
  char badpassword[MAXLENGTH]; 
  printf("Enter a word: ");
  scanf("%s", word); // polling for input
  bad_password(word, strlen(word), badpassword); // constructing output
  printf("Your bad password is %s\n", badpassword);
  return 0;
}
