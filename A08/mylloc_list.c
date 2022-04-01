#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BESTFIT 0 // best fit strategy

struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk* flist = NULL;

void* malloc (size_t size) {
  if (size == 0){
    return NULL;
  }
  // Step 1: check free list for memory
  // If found, remove it from the free list and return it
  struct chunk* prev = NULL;
  struct chunk* curr = flist;
  struct chunk* bestchunk = NULL;
  struct chunk* bestchunkprev = NULL;
  int bestsize = 999999;
  while (curr != NULL) {
    if (curr->size >= size) {
      if (BESTFIT && ((curr->size - size) < (bestsize-size))) {
        // potential best chunk
        bestchunk = curr;
        bestchunkprev = prev;
        bestsize = curr->size;
      } else if (!BESTFIT) {
        // first fit strategy
        if (prev != NULL) {
          prev->next = curr->next;
        } else {
          flist = curr->next;
        }
        curr->used = size;
        return (void*) (curr + 1);
      }
    }
    prev = curr;
    curr = curr->next;
  }
  if (BESTFIT && bestchunk != NULL) {
    // return best chunk
    if (bestchunkprev != NULL) {
      bestchunkprev->next = bestchunk->next;
    } else {
      flist = bestchunk->next;
    }
    bestchunk->used = size;
    return (void*) (bestchunk+1);
  }
  // Step 2: only allocate if memory not found in free list
  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) -1) {
    return NULL;
  } else {
    struct chunk* header = (struct chunk*) memory;
    header->size = size;
    header->used = size;
    header->next = NULL;
    return (void*) (header+1);
  }
}

void free(void *memory) {
  if (memory != NULL) {
    struct chunk* data = (struct chunk*) memory;
    struct chunk* header = data - 1;
    header->used = 0;
    header->next = flist;
    flist = header;
  }
  return;
}

void fragstats(void* buffer[], int len) {
  int n_free = 0, free = 0, n_used = 0, unused = 0; 
  int larg_unused = 0, small_unused = 99999, larg_free = 0, small_free = 99999;
  float avg_unused = 0.0, avg_free = 0.0; 
  for (int i=0; i < len; i++) {
    // check buffer for used chunks with unused space
    if (buffer[i] != NULL) {
      struct chunk* data = (struct chunk*) buffer[i];
      struct chunk* header = data - 1;
      n_used++;
      int unused_i = header->size - header->used;
      unused += unused_i;
      if (unused_i > larg_unused) {
        larg_unused = unused_i;
      } else if (unused_i < small_unused) {
        small_unused = unused_i;
      }
    }
  } 
  struct chunk* curr = flist;
  // check free list for unused chunks 
  while (curr != NULL) {
    n_free++;
    int free_i = curr->size;
    free += free_i;
    if (free_i > larg_free) {
      larg_free = free_i;
    } else if (free_i < small_free) {
      small_free = free_i;
    }
  curr = curr->next;
  }
  if (n_free != 0) {
    avg_free = (float) free/n_free;
  }
  if (n_used != 0) {
    avg_unused = (float) unused/n_used;
  }
  printf("Total blocks: %d Free: %d Used: %d\n", n_free+n_used, n_free, n_used);
  printf("Internal unused: total: %d average: %.1f smallest: %d largest: %d\n", unused, avg_unused, small_unused, larg_unused);
  printf("External unused: total: %d average: %.1f smallest: %d largest: %d\n", free, avg_free, small_free, larg_free);
}
