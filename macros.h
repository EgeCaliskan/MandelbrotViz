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
#define RATIO (((float)(RES_X))/((float)(RES_Y)))
#define MIN(X,Y) (((X) > (Y)) ? (Y) : (X))
#define ABS(X) (((X) > 0) ? (X) : -(X))
#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
#define BRIGHTNESS_MULTIPLIER 1
typedef struct{
    Vector2 Origin;
    float mult;
    float max_x;
    float max_y;
    float min_x;
    float min_y;
    int num_iterations;
  } StateHolder;
#endif

