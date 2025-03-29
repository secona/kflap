#include <iostream>
#include <vector>
#include <raylib.h>

class State {
public:
	std::string label;
	Vector2 position;

	State(int number, Vector2 pos) {
		position = pos;
		label = "q" + std::to_string(number);
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
	int stateCount = 0;
	std::vector<State> states;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	InitWindow(800, 450, "kflap");

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			State s(stateCount, GetMousePosition());
			states.push_back(s);
			stateCount++;
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			for (size_t i = 0; i < states.size(); i++) {
				State s = states[i];
				if (CheckCollisionPointCircle(GetMousePosition(), s.position, 20)) {
					states.erase(states.begin() + i);
				}
			}
		}

		for (State s : states) {
			s.draw();
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
