#ifndef MACROS
#define MACROS 
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define RES_X 2520
#define RES_Y 1680
#define WINDOW_X 2520
#define WINDOW_Y 1680
#define RATIO (((long double)(RES_X))/((long double)(RES_Y)))
#define MIN(X,Y) (((X) > (Y)) ? (Y) : (X))
#define ABS(X) (((X) > 0) ? (X) : -(X))
#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
#define BRIGHTNESS_MULTIPLIER 1
typedef struct{
    Vector2 Origin;
    long double mult;
    long double max_x;
    long double max_y;
    long double min_x;
    long double min_y;
    int num_iterations;
  } StateHolder;

typedef struct{
  long double x;
  long double y;
} Vector2L;
#endif

