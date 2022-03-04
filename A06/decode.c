/*
decode.c
Author: Keith Mburu
3/4/2022
Decodes image to get message
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

/*
Raises a base to an exponent
base: number to be raised
exponent: number to be raised to
returns result of exponentiaton
*/
unsigned int power(unsigned int base, int exp) {
  unsigned int result = 1;
  for (int i=0; i < exp; i++) {
    result *= base;
  }
  return result;
}

/*
Converts binary string to its ASCII representation
bin: binary string
returns ASCII character
*/
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
  if (argc != 2) {
    char usage[32] = "";
    for (int i = 0; i < argc; i++) {
      strcat(usage, argv[i]);
      strcat(usage, " ");
    }
    printf("usage: %s\n", usage);
    exit(0);
  }
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

  char* message = malloc(sizeof(char)*(max+1));
  memset(message, '\0', sizeof(char)*(max+1));

  int index = 0;
  unsigned int mask = 0x00000001;
  char bin[9];
  bin[8] = '\0';
  char decoded;
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      for (int k=0; k < 3; k++) {
        // last bit is 1
        if ((raster[i*w+j].colors[k] & mask) == 0x00000001) {
          bin[index % 8] = '1';
        }
        // last bit is 0
        else {
          bin[index % 8] = '0';
        }
        // size of typical ASCII character
        if ((index % 8) == 7) {
          decoded = bin_to_char(bin);
          //printf("bin: %s, decoded: %c\n", bin, decoded);
          // end of message or file
          if (decoded == '\0' || index == (max*8)-1) {
            if (index == (max*8)-1) {
              message[((index+1)/8)-1] = decoded;
            }
            //if (decoded == '\0') {
              //printf("\nNull char found\n");
            //}
            printf("%s", message);
            free(message);
            message = NULL; 
            free(raster);
            raster = NULL;
            exit(2); // finished decoding
          }
          // append character to message
          else {
            message[((index+1)/8)-1] = decoded;
            //printf("message: %s\n", message); 
          }
          //printf("bin: %s, char: %c, message: %s\n", bin, bin_to_char(bin), message);  
        }
        index++;
      }
    }
  }
  
  return 0;
}
