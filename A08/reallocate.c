#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
  void* init = sbrk(0);
  printf("The initial top of the heap is %p\n", init);  
  void* curr = sbrk(0);
  printf("The top of the heap after printf is %p\n", curr);
  unsigned int increase = curr - init;
  printf("Increased by %d (0x%X) bytes\n", increase, increase);
  for (int i=0; i < 10; i++) {
    void* memory = malloc(100);
    curr = sbrk(0);
    printf("The current top of the heap is %p\n", curr);
    increase = curr - init;
    printf("Increased by %d (0x%X) bytes\n", increase, increase);
    free(memory);
  }
  return 0;
}
