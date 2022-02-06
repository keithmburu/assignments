//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 20 // maximum snack name length
#define MAXNUMBER 10 // maximum number of snacks

struct snack {
  char name[32];
  float cost;
  int quantity;
  struct snack* next;
};

/*
Constructs the struct corresponding to each snack
name: snack name
cost: snack cost
quantity: snack quantity
returns: snack struct
*/
struct snack snack_struct(const char* name, float cost, int quantity) {
  struct snack x;
  strcpy(x.name, name);
  x.cost = cost;
  x.quantity = quantity;
  x.next = NULL;
  return x;
}

// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, 
    const char* name, float cost, int quantity) {
  struct snack new = snack_struct(name, cost, quantity);
  if (snacks == NULL) {
    snacks = &new;
  }
  else {
    struct snack* curr = snacks;
    struct snack* prev = NULL;
    int done = 0;
    while (!done) {
      if (new.name < curr->name) {
        new.next = curr;
        if (prev != NULL) {
          prev->next = &new;
        }
        else {
          snacks = &new;
        }
        done = 1;
      }
      else {
        curr = curr->next;
        prev = curr;
      }
    }
  }
  return snacks;
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  snacks = NULL;
}

int main() {
  struct snack* snacks = NULL; // linked list of snacks
  int adding; // number of snacks being added
  char name[MAXLENGTH];
  float cost;
  int quantity;
  
  printf("Enter a number of snacks: ");
  scanf("%d", &adding);
  for (int i = 0; i < adding; i++) {
    printf("Enter a name: ");
    scanf("%s", name);
    printf("Enter a cost: ");
    scanf("%f", &cost);
    printf("Enter a quantity: ");
    scanf("%d", &quantity);
    snacks = insert_sorted(snacks, name, cost, quantity);
    printf("%s", snacks->name);
  }
  
  printf("\nWelcome to Dynamic Donna's Snack Bar.\n\n");
  struct snack* curr = snacks;
  printf("naem: %s", snacks->name);
  exit(1);
  int i = 0;
  while (curr != NULL) {
    printf("%d) %-20s cost: $%-10.2f quantity: %d\n", i, curr->name, 
      curr->cost, curr->quantity);
    i++;
    curr = curr->next;
  }

  return 0;
}

