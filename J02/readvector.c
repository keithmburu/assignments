#include <stdio.h>
#include <stdlib.h>

// readvector opens and reads the given file
// The size of the vector should be stored in the parameter size
// The values should be returned in a flat float array
float* readvector(const char* filename, int *size) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Cannot open file \"%s\"\n", filename);
    exit(1);
  }
  fscanf(file, "%d ", size);
  float* result = malloc(sizeof(float) * *size);
  for (int i=0; i < *size; i++) {
    float x;
    fscanf(file, " %f", &x);
    result[i] = x; 
  }
  fclose(file);
  return result;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: readvector %s\n", argv[1]);
    exit(0);
  }

  int size = 0;
  float* vector = readvector(argv[1], &size);

  for (int i=0; i < size; i++) {
    printf("%f\n", vector[i]);
  }
  free(vector);
  return 0;
}

