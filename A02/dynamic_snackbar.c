/* 
dynamic_snackbar.c
Author: Keith Mburu
2/4/2022
Constructs a list of snacks available for purchase
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 20 // maximum snack name length
#define MAXNUMBER 10 // maximum number of snacks

/*
Struct with snack attributes
*/
struct snack {
  char name[32];
  float cost;
  int quantity;
};

/*
Constructs the struct corresponding to each snack
name: snack name
cost: snack cost
quantity: snack quantity
returns: snack struct
*/
struct snack snack_struct(char name[], float cost, int quantity) {
  struct snack x;
  strcpy(x.name, name);
  x.cost = cost;
  x.quantity = quantity;
  return x;
}

int main() {
  int adding = 0; // number of snacks being added
  char name[MAXLENGTH];
  float cost;
  int quantity;
  
  printf("Enter a number of snacks: ");
  scanf("%d", &adding);

  struct snack* snacks = malloc(sizeof(struct snack)*adding);// array of structs 
  for (int i = 0; i < adding; i++) {
    printf("Enter a name: ");
    scanf("%s", name);
    printf("Enter a cost: ");
    scanf("%f", &cost);
    printf("Enter a quantity: ");
    scanf("%d", &quantity);
    snacks[i] = snack_struct(name, cost, quantity);
  }
  
  printf("\nWelcome to Dynamic Donna's Snack Bar.\n\n");
  for (int i = 0; i < adding; i++) {
    printf("%d) %-20s cost: $%-10.2f quantity: %d\n", i, snacks[i].name, 
      snacks[i].cost, snacks[i].quantity);
  }
  
  free(snacks);
  snacks = NULL;
  return 0;
}
