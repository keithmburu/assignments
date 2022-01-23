#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bad_password(char password[], int size, char badpassword[]) {
  for (int i = 0; i < size; i++) {
    switch(password[i]) {
      case 'e':
        badpassword[i] = '3';
        break;
      case 'l':
        badpassword[i] = '1';
        break;
      case 'a':
        badpassword[i] = '@';
        break;
      default:
        badpassword[i] = password[i];
    }
  }
  badpassword[size] = '\0';
}

int main() {
  char password[10];
  char badpassword[10]; 
  printf("Enter a word: ");
  scanf("%s", &password);
  bad_password(password, strlen(password), badpassword);
  printf("Your bad password is %s\n", badpassword);
  return 0;
}
