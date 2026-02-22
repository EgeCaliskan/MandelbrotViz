#include "raylib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"
#include "macros.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void) {
  int num_iterations = 100;
  long double log_num_iterations;
  Color palette[256];
  StateHolder State;
  reset_state(&State);
  for(int i = 0; i < 255; i++) {
    long double t = i / 255.0L;
    palette[i] = (Color){(0 - t) * 29 + (241) * t,  (1-t) * 189 + (81) * t, (1 - t) * 230 + (94) * t, 255};
	}
	printf("RATIO: %f\n", RATIO);
	long double t0 = GetTime();
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
  long double zoom_level = 1;
  while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawTexture(texture, 0, 0, WHITE);
    bool panel_open = 0;
    if(GuiButton((Rectangle){2400, 50, 100, 100}, "#96#") )
      panel_open = !panel_open; 
    else if(IsKeyPressed(KEY_R))
    {
      reset_state(&State);
      img = StartingImage(&State);
      texture = LoadTextureFromImage(img);
      zoom_level = 1.0L;
    }

    else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
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
      State.num_iterations = 100 + log2(zoom_level) * 10; 
			drawing_rectangle = 0;
			Vector2 Pos = GetMousePosition();
			printf("Start(Original): %f %f\n", Start.x, Start.y);
			printf("End(Original): %f %f\n", Pos.x, Pos.y);
      update_Image(img.data, Start, Pos, &State);
			texture = LoadTextureFromImage(img);
			printf("NUM ITERATIONS: %d\n", State.num_iterations);
      zoom_level = 2.47L / (State.max_x - State.min_x);
      printf("ZOOM LEVEL: %Lf\n", zoom_level);
    }      
    DrawText(TextFormat("Zoom Level: %LE", zoom_level), 200, 100, 40, RED);
		EndDrawing();

	}
  UnloadImage(img); 
  CloseWindow();
}
