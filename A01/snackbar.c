/* 
snackbar.c
Author: Keith Mburu
1/28/2022
Maintain list of snacks available for purchase
*/

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 20 // maximum snack name length
#define MAXNUMBER 5 // maximum number of snacks

/*
Struct with snack attributes
*/
struct Snack {
  char name[MAXLENGTH];
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
struct Snack snack_struct(char name[], float cost, int quantity) {
  struct Snack x;
  strcpy(x.name, name);
  x.cost = cost;
  x.quantity = quantity;
  return x;
}

int main() {
  struct Snack CocoPuffs;
  struct Snack ManchegoCheese;
  struct Snack MagicBeans;
  struct Snack snacks[MAXNUMBER]; // array of structs
  int options; // number of snacks available
  int budget; 
  float fbudget; // budget converted to float
  int choice; // option chosen by buyer

  options = 0;
  CocoPuffs = snack_struct("Coco Puffs", 1.50, 4);
  snacks[0] = CocoPuffs;
  options++;
  
  ManchegoCheese = snack_struct("Manchego cheese", 15.50, 6);
  snacks[1] = ManchegoCheese;
  options++;

  MagicBeans = snack_struct("Magic beans", 0.50, 0);
  snacks[2] = MagicBeans;
  options++;

  printf("Welcome to Steven Struct's Snack Bar.\n\nHow much money do you have? ");
  scanf("%d", &budget);
  fbudget = (float)budget;
  
  while (1) {
    printf("\n");
    for (int i = 0; i < options; i++) {
      printf("%d) %-20s cost: $%-10.2f quantity: %d\n", i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
    }
    printf("\nWhat snack would you like to buy? [0, 1, 2] ");
    scanf("%d", &choice);
    
    if (snacks[choice].cost > fbudget) {
      printf("You can't afford it!\n");
      break;
    }
    else if (snacks[choice].quantity == 0) {
      printf("Sorry, we are out of %s\n", snacks[choice].name);
      break;
    }
    else {
      fbudget -= snacks[choice].cost;
      printf("You bought %s\nYou have $%.2f left\n", snacks[choice].name, fbudget);
    }
  }
  return 0;
}
