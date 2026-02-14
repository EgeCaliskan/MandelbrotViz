#include "func.h"
#include "raylib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <compute_utils.c>

#define RES_X 2520
#define RES_Y 1680
#define WINDOW_X 2520
#define WINDOW_Y 1680
#define RATIO (((float)(RES_X))/((float)(RES_Y)))
#define MIN(X,Y) (((X) > (Y)) ? (Y) : (X))
#define ABS(X) (((X) > 0) ? (X) : -(X))
#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
#define BRIGHTNESS_MULTIPLIER 1

Vector2 Origin = {0,0}; 
float mult = 1;
float max_x = 0.47;
float min_x = -2.00;
float max_y = 1.12;
float min_y = -1.12;

int num_iterations = 100;
float log_num_iterations;
Color palette[256];

int n_it(float cx, float cy){
	float zx = 0, zy = 0;
	float it = 0;
	float zx_new;
	while(it < num_iterations && zx * zx + zy * zy < 4)
	{
		zx_new = zx * zx - zy * zy + cx;
		zy = cy + 2 * zx * zy;
		it++;
		zx = zx_new;
	} return it;
}

Color color(int n, float cx, float cy)
{
	int c;
	if(cx *  cx + cy * cy > 400)
		c = ((int)(n + 1 - log(log(cx*cx + cy*cy))/log(2)) * 2) %  255; else c = ((n + 1) * 2) %  255; return (Color){0,c,0,255};
}
Vector2 to_mandelbrot_coordinates(Vector2 coord)
{
	Vector2 res;
	res.x = min_x + (coord.x) * (max_x - min_x) / RES_X;
	res.y = max_y -  (coord.y) * (max_y - min_y) / RES_Y;
	return res;
}

void CalculateMandelbrot(Color* pixelptr, Vector2 Start, Vector2 End)
{
	min_x = Start.x;
	max_x = End.x;
	max_y = Start.y;
	min_y = End.y;
	Color* p = pixelptr;
	double x_stepsize = (max_x - min_x) / RES_X;
	double y_stepsize = (max_y - min_y) / RES_Y;
	printf("START (MANDELBROT): %f %f\n", Start.x, Start.y);
	printf("END (MANDELBROT): %f %f\n",End.x, End.y);
	for(int y = 0; y < RES_Y; y++)
	void CalculateMandelbrot(Color* pixelptr, Vector2 Start, Vector2 End)
{
	min_x = Start.x;
	max_x = End.x;
	max_y = Start.y;
	min_y = End.y;
	Color* p = pixelptr;
	double x_stepsize = (max_x - min_x) / RES_X;
	double y_stepsize = (max_y - min_y) / RES_Y;
	printf("START (MANDELBROT): %f %f\n", Start.x, Start.y);
	printf("END (MANDELBROT): %f %f\n",End.x, End.y);
	for(int y = 0; y < RES_Y; y++)
	{
		for(int x = 0; x < RES_X; x++)
		{
			int val = n_it(Start.x + x_stepsize * x, Start.y - y_stepsize * y);
			*p =  color(val, Start.x + x_stepsize * x, Start.y - y_stepsize * y);
			p++;
		}
	}
} // MANDELBROT COORDS

{
		for(int x = 0; x < RES_X; x++)
		{
			int val = n_it(Start.x + x_stepsize * x, Start.y - y_stepsize * y);
			*p =  color(val, Start.x + x_stepsize * x, Start.y - y_stepsize * y);
			p++;
		}
	}
} // MANDELBROT COORDS

void update_Image(Color* pixelptr, Vector2 Start, Vector2 End)
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
	Vector2 ulm = to_mandelbrot_coordinates(UpperLeft);
	Vector2 lrm = to_mandelbrot_coordinates(LowerRight);
	CalculateMandelbrot(pixelptr, ulm, lrm);

}


Image StartingImage()
{

	float Mult = 1;
	Color* pixels = malloc(sizeof(Color) * RES_X * RES_Y);
	Color* p = pixels;

	if (pixels == NULL || p == NULL)
	{
		printf("Cannot allocate memory. Exiting.");
		exit(-1);
	}

	for(int y = 0; y < RES_Y; y++)
		for(int x = 0; x < RES_X; x++){
			int val = n_it(x * 2.47f / RES_X - 2.00f,  y * 2.24f / RES_Y - 1.12f );
			*p  = color(val, x * 2.47f / RES_X - 2.00f, y * 2.24f / RES_Y - 1.12f);
			p++;
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

int main(void)
{
	for(int i = 0; i < 255; i++)
	{
		double t = i / 255.00;
		palette[i] = (Color){(1 - t) * 29 + (241) * t,  (1-t) * 189 + (81) * t, (1 - t) * 230 + (94) * t, 255};
	}
	printf("RATIO: %f\n", RATIO);
	double t0 = GetTime();
	InitWindow(WINDOW_X, WINDOW_Y, "Mandelbrot");
	BeginDrawing();
	ClearBackground(WHITE);
	EndDrawing();
	SetTargetFPS(60);
	Image img = StartingImage();
	Texture2D texture = LoadTextureFromImage(img);

	Vector2 Start = {-1,-1};
	Vector2 End = {-1,-1};
	int drawing_rectangle = 0;
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawTexture(texture, 0, 0, WHITE);
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			if(!drawing_rectangle)
			{
				drawing_rectangle = 1;
				Start = GetMousePosition();
			}
			Vector2 Pos = GetMousePosition();
			DrawRectangleLines(Start.x, Start.y, Pos.x - Start.x, Pos.y - Start.y, RED);
		}
		else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			num_iterations = 100 + log2(2.47 / (max_x - min_x)) * 10; 
			drawing_rectangle = 0;
			Vector2 Pos = GetMousePosition();
			printf("Start(Original): %f %f\n", Start.x, Start.y);
			printf("End(Original): %f %f\n", Pos.x, Pos.y);
			update_Image(img.data, Start,Pos);
			texture = LoadTextureFromImage(img);
			log_num_iterations = log10(num_iterations);
			printf("NUM ITERATIONS: %d\n", num_iterations);
		}
		EndDrawing();

	}

	UnloadImage(img);
	CloseWindow();

}
