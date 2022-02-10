#include <string.h>
#include <stdio.h>

void main() {
  char word[32];
  char symbol;
  int wordlen;

  printf("Please enter a word: ");
  scanf(" %s", word);
  wordlen = strlen(word);
  printf("Please enter a symbol: ");
  scanf(" %c", &symbol);
  
  for (int i = 0; i < (wordlen+4); i++) {
    printf("%c", symbol);
  }
  printf("\n");
  printf("%c %s %c\n", symbol, word, symbol);
  for (int i = 0; i < (wordlen+4); i++) {
    printf("%c", symbol);
  }
  printf("\n");
}
