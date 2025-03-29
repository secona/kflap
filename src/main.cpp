#include <iostream>
#include <vector>
#include <raylib.h>

enum Tools {
	TOOL_STATE = KEY_ONE,
	TOOL_TRANSITION = KEY_TWO,
};

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

	Tools tool = TOOL_STATE;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	InitWindow(800, 450, "kflap");

	while (!WindowShouldClose()) {
		if (IsKeyPressed(TOOL_STATE)) tool = TOOL_STATE;
		if (IsKeyPressed(TOOL_TRANSITION)) tool = TOOL_TRANSITION;

		BeginDrawing();

		ClearBackground(RAYWHITE);

		switch (tool) {
		case TOOL_STATE:
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
			break;

		case TOOL_TRANSITION:
			;
		}

		for (State s : states) {
			s.draw();
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
