#include "macros.h"
#include "func.h"
#include "raylib.h"
Color color(int n, float cx, float cy);
Vector2 to_mandelbrot_coordinates(Vector2 coord, StateHolder* StatePtr); 
Image StartingImage(StateHolder* StatePtr);
void update_Image(Color* pixelptr, Vector2 Start, Vector2 End, StateHolder* StatePtr);
void CalculateMandelbrot(Color* pixelptr, Vector2 Start, Vector2 End, StateHolder* StatePtr)
{ 
  StatePtr->min_x = Start.x;
  StatePtr->max_x = End.x;
  StatePtr->max_y = Start.y;
  StatePtr->min_y = End.y;
	Color* p = pixelptr;
  double x_stepsize = (End.x - Start.x) / RES_X;
	double y_stepsize = (Start.y - End.y) / RES_Y;
	printf("START (MANDELBROT): %f %f\n", Start.x, Start.y);
	printf("END (MANDELBROT): %f %f\n",End.x, End.y);
  for(int y = 0; y < RES_Y; y++)
	{
		for(int x = 0; x < RES_X; x++)
		{
			int val = n_it(Start.x + x_stepsize * x, Start.y - y_stepsize * y, StatePtr);
			*p =  color(val, Start.x + x_stepsize * x, Start.y - y_stepsize * y);
			p++;
		}
	}
} // MANDELBROT COORDS




Color color(int n, float cx, float cy)
{ int c;
	if(cx *  cx + cy * cy > 400)
		c = ((int)(n + 1 - log(log(cx*cx + cy*cy))/log(2)) * 2) %  255;
  else c = ((n + 1) * 2) %  255; 
  return (Color){0,c,0,255};
}

Vector2 to_mandelbrot_coordinates(Vector2 coord, StateHolder* StatePtr)
{
	Vector2 res;
	res.x = StatePtr -> min_x + (coord.x) * (StatePtr -> max_x - StatePtr -> min_x) / RES_X;
	res.y = StatePtr -> max_y -  (coord.y) * (StatePtr -> max_y - StatePtr -> min_y) / RES_Y;
	return res;
}

Image StartingImage(StateHolder* StatePtr)
{

	float Mult = 1;
	Color* pixels = malloc(sizeof(Color) * RES_X * RES_Y);
	Color* p = pixels;

	if (pixels == NULL || p == NULL)
	{
		printf("Cannot allocate memory. Exiting."); exit(-1); }

	for(int y = 0; y < RES_Y; y++)
  {
    if(y % 100 == 0) 
    printf("Starting Row: %d\n",y );		
    for(int x = 0; x < RES_X; x++){
			int val = n_it(x * 2.47f / RES_X - 2.00f,  y * 2.24f / RES_Y - 1.12f, StatePtr); 
      *p  = color(val, x * 2.47f / RES_X - 2.00f, y * 2.24f / RES_Y - 1.12f);
      p++;
    }
	}


	Image img = {
		.width = RES_X,
		.height = RES_Y,
		.data = pixels,
		.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
		.mipmaps = 1,
		};

	return img;
}


void update_Image(Color* pixelptr, Vector2 Start, Vector2 End, StateHolder* StatePtr)
{

	Vector2 UpperLeft, LowerRight;
	UpperLeft.x = MIN(Start.x, End.x);
	UpperLeft.y = MIN(Start.y, End.y);
	LowerRight.x = MAX(Start.x, End.x);
	LowerRight.y = MAX(Start.y, End.y);
	printf("UpperLeft: %f %f\n", UpperLeft.x, UpperLeft.y);
	printf("LowerRight: %f %f\n", LowerRight.x, LowerRight.y);
	float height = LowerRight.y - UpperLeft.y;
	float width  = LowerRight.x - UpperLeft.x;
	float ratio = width / height;
	float scaled_height = height;
	float scaled_width = width;
	printf("WIDTH: %f\n", width);
	printf("HEIGHT: %f\n", height);
	printf("SCALED HEIGHT (1): %f\n", scaled_height);
	if(ratio < RATIO) //   HEIGHT
		scaled_width = RATIO * height;
	else
		scaled_height = (float)width / (float)RATIO;
	LowerRight.x = UpperLeft.x + scaled_width;
	LowerRight.y = UpperLeft.y + scaled_height;
	Vector2 ulm = to_mandelbrot_coordinates(UpperLeft, StatePtr);
	Vector2 lrm = to_mandelbrot_coordinates(LowerRight, StatePtr);
	CalculateMandelbrot(pixelptr, ulm, lrm, StatePtr); 
}
