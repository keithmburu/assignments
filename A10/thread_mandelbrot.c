/*
thread_mandelbrot.c
Author: Keith Mburu
4/22/2022
Generates the mandelbrot set using multiple threads
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include <string.h>
#include <math.h>
#include <pthread.h>

struct threadData {
  int id;
  int rowstart;
  int rowend;  
  int colstart;                         
  int colend; 
  struct ppm_pixel* raster;
  struct ppm_pixel* palette;
  int size;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  int maxIterations;
  pthread_mutex_t* mutex;
};
  
void mandelbrot(void* threadData_i) {
  struct threadData* data = (struct threadData*) threadData_i;
  // compute image
  for (int col = data->colstart; col < data->colend; col++) {
    for (int row = data->rowstart; row < data->rowend; row++) {
      float xfrac = (float) (col+1) / data->size;
      float yfrac = (float) (row+1) / data->size;
      float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
      float y0 = data->ymin + yfrac * (data->ymax - data->ymin);
      //printf("xfrac: %f yfrac: %f x0: %f y0: %f\n", xfrac, yfrac, x0, y0);
      float x = 0;
      float xtmp;
      float y = 0;
      int iter = 0;
      while ((iter < data->maxIterations) && ((x*x + y*y) < 2*2)) {
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
        //printf("x: %d y: %d iter: %d\n", x, y, iter);
      }
      struct ppm_pixel color;
      if (iter < data->maxIterations) { // escaped
        color = data->palette[iter];
        //printf("r: %d g: %d b: %d\n", color.red, color.green, color.blue);
      } else {
        struct ppm_pixel black = {{{0, 0, 0}}};
        color = black;
      }
      pthread_mutex_lock(data->mutex);
      // write color to image at location (row,col)
      (data->raster)[(row*(data->size))+col] = color;
      pthread_mutex_unlock(data->mutex);
    }
  }
  printf("Thread %d) finished\n", data->id);
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numThreads = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymin = atof(optarg); break;
      case 'b': ymax = atof(optarg); break;
      case 'p': numThreads = atoi(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numThreads>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num threads = %d\n", numThreads);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  struct ppm_pixel* raster = malloc(sizeof(struct ppm_pixel)*size*size);
  if (raster == NULL) {
    printf("raster malloc failed\n");
    exit(1);
  }
  memset(raster, 0, sizeof(struct ppm_pixel)*size*size);
  
  // timer
  struct timeval tstart, tend;
  double timer;
  srand(time(0));
  gettimeofday(&tstart, NULL);

  // generate pallet
  struct ppm_pixel* palette = malloc(maxIterations * sizeof(struct ppm_pixel));
  if (palette == NULL) {
    printf("palette malloc failed\n");
    exit(1);
  }
  memset(palette, 0, maxIterations * sizeof(struct ppm_pixel));
  for (int i=0; i < maxIterations; i++) {
    struct ppm_pixel color;
    color.red = rand() % 255;
    color.green = rand() % 255;
    color.blue = rand() % 255;
    palette[i] = color;
  }
  struct ppm_pixel black = {{{0, 0, 0}}};

  pthread_t* tids = malloc(sizeof(pthread_t) * numThreads);
  if (palette == NULL) {
    printf("tids malloc failed\n");
    exit(1);
  }
  memset(tids, 0, sizeof(pthread_t) * numThreads);

  int rowstart = 0;
  int rowend = size/sqrt(numThreads);
  int colstart = 0;
  int colend = size/sqrt(numThreads); 
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);
  struct threadData* dataArr = malloc(sizeof(struct threadData)*numThreads);
  memset(dataArr, 0, sizeof(struct threadData)*numThreads);
  for (int i = 0; i < numThreads; i++) {
    pthread_t thread_i;
    tids[i] = thread_i; 
    int id = i+1;
    struct threadData threadData_i = {id, rowstart, rowend, colstart, colend,
      raster, palette, size, xmin, xmax, ymin, ymax, maxIterations, &mutex};
    dataArr[i] = threadData_i;
    printf("Thread %d) Sub-image block: cols (%d, %d) to rows (%d,%d)\n", id, \
      rowstart, rowend, colstart, colend);
    pthread_create(&thread_i, NULL, (void*) mandelbrot, (void*) &dataArr[i]);
    if (i == sqrt(numThreads)-1) {
      colstart += size/sqrt(numThreads);
      colend += size/sqrt(numThreads);
      rowstart = 0;
      rowend = size/sqrt(numThreads);
    } else {
      rowstart += size/sqrt(numThreads);
      rowend += size/sqrt(numThreads);
    }
  }

  for (int i = 1; i <= numThreads; i++) {
    pthread_join(tids[i], NULL);
  }
  pthread_mutex_destroy(&mutex);
  
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec) \
    /1.e6;
  printf("Computed mandelbrot set (%dx%d) in %.6g seconds\n", size, size,\
    timer);
  char filename[32];
  sprintf(filename, "mandelbrot-%d-%ld.ppm", size, time(0));
  write_ppm(filename, raster, size, size);
  free(tids);
  free(palette);
  free(raster);
  return 0;
}
