#include <iostream>
#include <raylib.h>

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	InitWindow(800, 450, "kflap");

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Hello, world!", 800/2, 450/2, 14, LIGHTGRAY);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
