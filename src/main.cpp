#include "finite_automaton/core.h"
#include "finite_automaton/raylib.h"
#include <vector>
#include <raylib.h>

enum Tools {
	TOOL_STATE = KEY_ONE,
	TOOL_TRANSITION = KEY_TWO,
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
			draw_state(s);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
