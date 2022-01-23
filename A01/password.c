#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* bad_password(char password[], int size, char* badpassword[]) {
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
}

int main() {
  char password[10];
  char output[10];
  char badpassword[10]; 
  printf("Enter a word: ");
  scanf("%s", &password);
  bad_password(password, strlen(password), badpassword);
  for (int i = 0; i < strlen(password); i++) {
    printf("%d", i);
    output[i] = *(badpassword + 1);
  }
  printf("Your bad password is %s", output);
  return 0;
}
