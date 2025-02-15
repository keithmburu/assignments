//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name: Keith Mburu
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Initialize a pointer to a new struct node, which itself points to the top 
//  node of the stack
// Param sym: a character symbol corresponding to the new node
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack
// Returns the new node's address
struct node* structify(char sym, int line, int col, struct node* top) {
  struct node* x = malloc(sizeof(struct node));
  x->sym = sym;
  x->linenum = line;
  x->colnum = col;
  x->next = top;
  return x;
}

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  top = structify(sym, line, col, top);
  return top;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  struct node* newTop = top->next;
  free(top);
  top = NULL;
  return newTop;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  while (top != NULL) {
    struct node* temp = top;
    top = top->next;
    free(temp);
    temp = NULL;
  }
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  while (top != NULL) {
    printf("%c\n", top->sym);
    top = top->next;
  }
}

// Find matching braces and unmatched braces
// Param sym: a character symbol from the file
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param symbols: the address of the top node of the stack
// Param file: the program whose braces are being checked
void run(char sym, int linenum, int colnum, struct node* symbols, FILE* file) {
  while ((sym = fgetc(file)) != EOF) {
    if (sym == '\n') {
      linenum++;
      colnum = 0;
    }
    else {
      colnum++;
      if (sym == '{') {
        symbols = push(sym, linenum, colnum, symbols);
      }
      else if (sym == '}') {
        if (symbols == NULL) {
           printf("Unmatched brace on Line %d and Column %d\n", linenum, 
            colnum);
        }
        else if (symbols->sym == '}') {
           printf("Push and pop symbol mismatch!\n");
           exit(3);
        } 
        else {
          printf("Found matching braces: (%d, %d) -> (%d, %d)\n", 
            symbols->linenum, symbols->colnum, linenum, colnum);
          symbols = pop(symbols);
        }
      }
    } 
  }
  while (symbols != NULL) {
    printf("Unmatched brace on Line %d and Column %d\n", symbols->linenum, 
      symbols->colnum);
    symbols = pop(symbols);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    char usage[32] = "";
    for (int i = 0; i < argc; i++) {
      strcat(usage, argv[i]);
      strcat(usage, " ");
    }
    printf("usage: %s\n", usage);
    exit(1);
  }
  char filename[32] = "./";
  strcat(filename, argv[1]);
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
     printf("Cannot open file: %s\n", argv[1]);
     exit(2);
  }
  int linenum = 1;
  int colnum = 0;
  char sym; 
  struct node* symbols = NULL;

  run(sym, linenum, colnum, symbols, file);
  clear(symbols);
  fclose(file);
  return 0;
}
