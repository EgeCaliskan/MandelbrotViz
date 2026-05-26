#include "raylib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"
#include "macros.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "scroll_panel.h"

int main(void) {
    // initializing variables
    
    int num_iterations = 100;
    long double log_num_iterations;
    Color palette[256];
    StateHolder State;
    reset_state(&State);
    Vector2L MStart = {State.min_x, State.min_y};
    Vector2L MEnd = {State.max_x, State.max_y}; 
    Vector2 Start, End;
    int panel_max_width = 200; 
    int drawing_rectangle = 0;
    long double zoom_level = 1;
    bool is_panel_open = 0;
    bool mouse_touching_panel = 0;
    // creating the color palette 
    for(int i = 0; i < 255; i++) {
        long double t = i / 255.0L;
        palette[i] = (Color){(0 - t) * 29 + (241) * t,  (1-t) * 189 + (81) * t, (1 - t) * 230 + (94) * t, 255};
    }

    // setting the window
    InitWindow(WINDOW_X, WINDOW_Y, "Mandelbrot");
    GuiLoadStyle("style_cyber.rgs");
    GuiSetIconScale(3);
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
    SetTargetFPS(60);

    // generate and load initial image
    Image img = BlankStartingImage();
    update_Image_abs(img.data, MStart, MEnd, &State); 
    Texture2D texture = LoadTextureFromImage(img);
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(texture, 0, 0, WHITE);

        Rectangle Button = {1550, 50, 100, 100};
        Rectangle Camera = {1700, 50, 100, 100};
        bool mouse_touching_button = CheckCollisionPointRec(GetMousePosition(), Button) || CheckCollisionPointRec(GetMousePosition(), Camera);
        bool mouse_touching_panel = CheckCollisionPointRec(GetMousePosition(), panelRec);
        if(GuiButton((Rectangle){1550, 50, 100, 100}, "#96#"))
            is_panel_open = 0;
        if(GuiButton((Rectangle){1700, 50, 100, 100}, "#183#"))
            ExportImage(img, "./gallery/img.png");
        Vector2 Pos = GetMousePosition();
        if(drawing_rectangle)
            DrawRectangleLines(Start.x, Start.y, Pos.x - Start.x, Pos.y - Start.y, RED);
        if(!mouse_touching_panel && !mouse_touching_button)
        {
            if(IsKeyPressed(KEY_R))
            {
                reset_state(&State);
                update_Image_abs(img.data, MStart, MEnd, &State);
                texture = LoadTextureFromImage(img);
                zoom_level = 1.0L;
            }

            else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                if(!drawing_rectangle)
                {
                    drawing_rectangle = 1;
                    Start = GetMousePosition();
                }
            }
            else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && drawing_rectangle)
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

        }
        DrawText(TextFormat("Zoom Level: %LE", zoom_level), 200, 100, 40, RED);
        if(is_panel_open)
            panel_open();
        EndDrawing();

    }
    UnloadImage(img); 
    CloseWindow();
}
