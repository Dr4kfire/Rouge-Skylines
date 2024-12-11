#include <raylib.h>

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Rouge Skylines v0.1");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {   
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }
    
    CloseWindow();
}