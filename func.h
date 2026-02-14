#include "raylib.h"
#include "macros.h"
static inline int n_it(float cx, float cy, StateHolder* StatePtr)  
{
  float zx = 0, zy = 0;
	float it = 0;
	float zx_new;
	while(it < StatePtr -> num_iterations && zx * zx + zy * zy < 4)
	{
		zx_new = zx * zx - zy * zy + cx;
		zy = cy + 2 * zx * zy;
		it++;
		zx = zx_new;
	} 
  return it;
}
Color color(int n, float cx, float cy);
Vector2 to_mandelbrot_coordinates(Vector2 coord, StateHolder* StatePtr); 
Image StartingImage(StateHolder* StatePtr);
void update_Image(Color* pixelptr, Vector2 Start, Vector2 End, StateHolder* StatePtr);

