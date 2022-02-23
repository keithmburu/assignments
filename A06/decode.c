#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

unsigned int power(unsigned int base, int exp) {
  unsigned int result = 1;
  for (int i=0; i < exp; i++) {
    result *= base;
  }
  return result;
}

char bin_to_char(char* bin) {
  int character = 0;
  for (int i=0; i < 8; i++) {
    if (bin[i] == '1') {
      character += power(2, 7-i);
    }
  }
  return character;
}

int main(int argc, char** argv) {
  char* filename = argv[1];
  int w, h;
  struct ppm_pixel* raster = read_ppm(filename, &w, &h);
  if (raster == NULL) {
    printf("Could not create raster\n");
    exit(1);
  }
  printf("Reading %s with width %d and height %d\n", filename, w, h); 
  int max = (w * h * 3)/8;
  printf("Max number of characters in the image: %d\n", max);

  char* encoded = malloc((sizeof(char)*(max+1)*8));  
  memset(encoded, '\0', ((sizeof(char)*(max+1)*8)));
  unsigned int mask = 0b00000001;
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      for (int k=0; k < 3; k++) {
        char bit;
        if ((raster[i*w+j].colors[k] & mask) == 0b00000001) {
          bit = '1';
        }
        else {
          bit = '0';
        }
        encoded[(i*w*3)+(j*3)+k] = bit;
      }
    }
  }
  free(raster);
  raster = NULL;

  //printf("encoded: %s\n", encoded)

  char* message = malloc(max);
  memset(message, '\0', max);
  char bin[8] = "00000000";
  for (int i=0; i < strlen(encoded); i++) {
    bin[i % 8] = encoded[i];
    //printf("i: %d, encoded[i]: %c, bin: %s\n", i, encoded[i], bin);
    if (((i+1) % 8) == 0) {
      message[((i+1)/8)-1] = bin_to_char(bin);
      //printf("bin: %s, char: %c, message: %s\n", bin, bin_to_char(bin), message);
      memset(bin, '0', 8);
    }
  }
  printf("%s", message);

  free(encoded);
  //free(message);
  return 0;
}
