#include <iostream>
#include <raylib.h>

class State {
public:
	std::string label;
	Vector2 position;

	State(Vector2 pos) {
		position = pos;
		label = "q0";
	}

	void draw() {
		const int fontSize = 14;

		int textW = MeasureText(label.c_str(), fontSize);
		int textH = fontSize;

		int textX = position.x - textW / 2;
		int textY = position.y - textH / 2;

		DrawCircleV(position, 20, LIGHTGRAY);
		DrawText(label.c_str(), textX, textY, fontSize, BLACK);
	}
};

int main() {
	Vector2 v{200, 200};
	State s(v);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	InitWindow(800, 450, "kflap");

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Hello, world!", 800/2, 450/2, 14, LIGHTGRAY);
		s.draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
