/*
password.c
Author: Keith Mburu
1/28/2022
Convert password to bad password
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 10 // maximum password length

/* 
Converts password given by the user to a bad password
password: input from user
size: length of password
badpassword: output to be constructed
*/
void bad_password(char password[], int size, char badpassword[]) {
  for (int i = 0; i < size; i++) {
    switch(password[i]) { 
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
        badpassword[i] = password[i];
    }
  }
  badpassword[size] = '\0'; // terminate string
}

int main() {
  char password[MAXLENGTH];
  char badpassword[MAXLENGTH]; 
  printf("Enter a word: ");
  scanf("%s", &password); // polling for input
  bad_password(password, strlen(password), badpassword); // constructing output
  printf("Your bad password is %s\n", badpassword);
  return 0;
}
