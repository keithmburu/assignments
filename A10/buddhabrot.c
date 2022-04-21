/*
buddhabrot.c
Author: Keith Mburu
4/22/2022
Generates the buddhabrot set using multiple threads
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
  pthread_barrier_t* barrier;
  int* membership;
  int* counts;
  int* maxCount;
};
   
void mandelbrot(struct threadData* data) {
  for (int row = data->rowstart; row < data->rowend; row++) {
    for (int col = data->colstart; col < data->colend; col++) {
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
      
      pthread_mutex_lock(data->mutex);
      if (iter < data->maxIterations) { // escaped
        data->membership[(row*(data->size))+col] = 0;
      } else {
        data->membership[(row*(data->size))+col] = 1;
      }
      pthread_mutex_unlock(data->mutex);
    }
  }
  printf("Thread %d) finished mandelbrot\n", data->id);
}

void counts(struct threadData* data) {
  for (int row = data->rowstart; row < data->rowend; row++) {
    for (int col = data->colstart; col < data->colend; col++) {
      if (data->membership[(row*data->size)+col] == 1) continue; //in mandelbrot
      float xfrac = (float) (col+1) / data->size;
      float yfrac = (float) (row+1) / data->size;
      float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
      float y0 = data->ymin + yfrac * (data->ymax - data->ymin);
      //printf("xfrac: %f yfrac: %f x0: %f y0: %f\n", xfrac, yfrac, x0, y0);
      float x = 0;
      float xtmp;
      float y = 0;
      while ((x*x + y*y) < 2*2) {
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        //printf("x: %d y: %d iter: %d\n", x, y, iter);
        int yrow = round(data->size * (y - data->ymin)/(data->ymax - data->ymin));
        int xcol = round(data->size * (x - data->xmin)/(data->xmax - data->xmin));
        if (yrow < 0 || yrow >= data->size) continue; // out of range
        if (xcol < 0 || xcol >= data->size) continue; // out of range
        pthread_mutex_lock(data->mutex);
        data->counts[(yrow*data->size)+xcol]++;
        if (data->counts[(yrow*data->size)+xcol] > *(data->maxCount)) {
          *(data->maxCount) = data->counts[(yrow*data->size)+xcol];
        }
        pthread_mutex_unlock(data->mutex);
        //printf("uncounted\n");
      }
    }
  }
  printf("Thread %d) finished counts\n", data->id);
}

void colors(struct threadData* data) {
  float gamma = 0.681;
  float factor = 1.0/gamma;
  for (int row = data->rowstart; row < data->rowend; row++) {
    for (int col = data->colstart; col < data->colend; col++) {
      float value = 0.0;
      //printf("%d\n", row*data->size+col);
      //printf("%d\n\n", data->counts[(row*data->size)+col]); 
      if (data->counts[(row*data->size)+col] > 0) {
        value = (float) log(data->counts[(row*data->size)+col]) / log(*(data->maxCount));
        value = (float) pow(value, factor);
        //printf("value: %f\n", value);
      }
      struct ppm_pixel color;
      color.red = value * 255;
      color.green = value * 255;
      color.blue = value * 255;
      pthread_mutex_lock(data->mutex);
      //printf("r: %d g: %d b: %d\n", color.red, color.green, color.blue);
      // write color to image at location (row,col)
      data->raster[(row*(data->size))+col] = color;
      pthread_mutex_unlock(data->mutex);
    }
  }
  printf("Thread %d) finished colors\n", data->id);
}

// thread routine
void run(void* threadData_i) {
  struct threadData* data = (struct threadData*) threadData_i;
  mandelbrot(data);
  counts(data);
  // wait until all counts are computed
  pthread_barrier_wait(data->barrier);
  colors(data);
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
  if (tids == NULL) {
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
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, NULL, numThreads);
  int* membership = malloc(sizeof(int)*size*size);
  if (membership == NULL) {
    printf("membership malloc failed\n");
    exit(1);
  }
  memset(membership, 0, sizeof(int)*size*size);
  int* maxCount = malloc(sizeof(int));
  *maxCount = 0;
  int* counts = malloc(sizeof(int)*size*size);
  if (counts == NULL) {
    printf("counts malloc failed\n");
    exit(1);
  }
  memset(counts, 0, sizeof(int)*size*size);
  struct threadData* dataArr = malloc(sizeof(struct threadData)*numThreads);
  memset(dataArr, 0, sizeof(struct threadData)*numThreads);
  for (int i = 0; i < numThreads; i++) {
    int id = i+1;
    struct threadData threadData_i = {id, rowstart, rowend, colstart, colend, 
      raster, palette, size, xmin, xmax, ymin, ymax, maxIterations, &mutex, \
      &barrier, membership, counts, maxCount};
    dataArr[i] = threadData_i;
    printf("Thread %d) Sub-image block: cols (%d, %d) to rows (%d,%d)\n", id, \
      rowstart, rowend, colstart, colend);
    pthread_create(&tids[i], NULL, (void*) run, (void*) &dataArr[i]);
    if (i == sqrt(numThreads)-1) {
      rowstart += size/sqrt(numThreads);
      rowend += size/sqrt(numThreads);
      colstart = 0;
      colend = size/sqrt(numThreads);
    } else {
      colstart += size/sqrt(numThreads);
      colend += size/sqrt(numThreads);
    }
  }

  for (int i = 0; i < numThreads; i++) {
    pthread_join(tids[i], NULL);
  }
  pthread_mutex_destroy(&mutex);  
  pthread_barrier_destroy(&barrier);  

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec) \
    /1.e6;
  printf("Computed buddhabrot set (%dx%d) in %.6g seconds\n", size, size,\
    timer);
  char filename[32];
  sprintf(filename, "buddhabrot-%d-%ld.ppm", size, time(0));
  write_ppm(filename, raster, size, size);
  free(counts);
  free(maxCount);
  free(membership);
  free(tids);
  free(palette);
  free(raster);
  free(dataArr);
  return 0;
}
