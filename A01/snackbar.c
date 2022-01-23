#include <stdio.h>
#include <string.h>

struct Snack {
  char name[10];
  float cost;
  int quantity;
}

snack_struct(char name[], float cost, int quantity) {
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
  struct Snack snacks[5];
  int options;
  int budget;
  int choice;

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

  while (1) {
    printf("\n");
    for (int i = 0; i < options; i++) {
      printf("%d) %-25s cost: $%-10g quantity: %d\n", i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
    }
    printf("\nWhat snack would you like to buy? [0, 1, 2] ");
    scanf("%d", &choice);
    
    if (snacks[choice].cost > budget) {
      printf("\nYou can't afford it!\n");
    }
    else if (snacks[choice].quantity == 0) {
      printf("Sorry, we are out of %s\n", snacks[choice].name);
    }
    else {
      budget -= snacks[choice].cost;
      printf("\nYou bought %s\nYou have $%.2g left\n", snacks[choice].name, budget);
    }
  }
  return 0;
}
