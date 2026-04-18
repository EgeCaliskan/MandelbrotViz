#include "raylib.h"
#include "macros.h"
#include <omp.h>


static inline int n_it(long double cx, long double cy, StateHolder* StatePtr)  
{
  long double zx = 0.0L, zy = 0.0L;
	long double it = 0.0L;
	long double zx_new;
  
	while(it < StatePtr -> num_iterations && zx * zx + zy * zy < 4.0L)
	{
		zx_new = zx * zx - zy * zy + cx;
		zy = cy + 2.0L * zx * zy;
		it++;
		zx = zx_new;
	} 
  return it;
}
Color color(int n, long double cx, long double cy);
Vector2L to_mandelbrot_coordinates(Vector2L coord, StateHolder* StatePtr); 
Image StartingImage(StateHolder* StatePtr);
void update_Image(Color* pixelptr, Vector2 Start, Vector2 End, StateHolder* StatePtr);
void reset_state(StateHolder* StatePtr);
void update_Image_abs(Color* pixelptr, Vector2L Start, Vector2L End, StateHolder* StatePtr);
Image BlankStartingImage();
