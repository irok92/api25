#include "raylib.h"

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Raylib Test");
    SetTargetFPS(60);

    // Define the camera to look into our 3d world
    Camera3D camera = {
        .target = (Vector3){ 0.0f, 0.0f, 0.0f },
        .position = (Vector3){ 10.0f, 10.f, 10.0f }, // camera diagonal.
        .up = (Vector3){ 0.0f, 1.0f, 0.0f}, // What direction is up.
        .fovy = 75.0f, // Field of view
        .projection = CAMERA_PERSPECTIVE
    };

    Vector3 cube_position = { 0.0f, 0.0f, 0.0f };

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(GRAY);

            BeginMode3D(camera);
                DrawCube(cube_position, 2.0f, 2.0f, 2.0f, RED);
                DrawGrid(10, 1.0f);
            EndMode3D();

            DrawText("Test", 10, 10, 16, (Color){ 0xFF, 0xFF, 0xFF, 0xFF});
        EndDrawing();
    }

    CloseWindow();

    return 0;
}