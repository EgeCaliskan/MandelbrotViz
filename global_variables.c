#include "raylib.h"
#include "global_variables.h"
Vector2 Origin = {0,0}; 
float mult = 1;
float max_x = 0.47;
float min_x = -2.00;
float max_y = 1.12;
float min_y = -1.12;

int num_iterations = 100;
float log_num_iterations;
Color palette[256];

typedef struct{
  Vector2 Origin = Origin;
  float mult = mult;
  float max_x = max_x;
  float max_y = max_y;
  float min_x = min_x;
  float min_y = min_y;
  int num_iterations = num_iterations;
};
