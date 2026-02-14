#include "raylib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"
#include "macros.h"


int main(void) {
  int num_iterations = 100;
  float log_num_iterations;
  Color palette[256];
  StateHolder State;
  State.Origin =(Vector2) {0,0};
  State.mult = 1;
  State.max_x = 0.47;
  State.max_y = 1.12;
  State.min_x = -2.00;
  State.min_y = -1.12;
  State.num_iterations = 100;
  for(int i = 0; i < 255; i++)
	{
		double t = i / 255.00;
		palette[i] = (Color){(0 - t) * 29 + (241) * t,  (1-t) * 189 + (81) * t, (1 - t) * 230 + (94) * t, 255};
	}
	printf("RATIO: %f\n", RATIO);
	double t0 = GetTime();
	InitWindow(WINDOW_X, WINDOW_Y, "Mandelbrot");
	BeginDrawing();
	ClearBackground(WHITE);
	EndDrawing();
	SetTargetFPS(60);
	Image img = StartingImage(&State);
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
			DrawRectangleLines(Start.x, Start.y, Pos.x - Start.x, Pos.y - Start.y, RED); }
		else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			State.num_iterations = 100 + log2(2.47 / (State.max_x - State.min_x)) * 10; 
			drawing_rectangle = 0;
			Vector2 Pos = GetMousePosition();
			printf("Start(Original): %f %f\n", Start.x, Start.y);
			printf("End(Original): %f %f\n", Pos.x, Pos.y);
      update_Image(img.data, Start, Pos, &State);
			texture = LoadTextureFromImage(img);
			log_num_iterations = log10(num_iterations);
			printf("NUM ITERATIONS: %d\n", num_iterations);
		}
		EndDrawing();

	}

	UnloadImage(img);
	CloseWindow();
}
