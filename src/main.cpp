#include <raylib.h>

#include <vector>

#include "finite_automaton/core.h"
#include "finite_automaton/raylib.h"

enum Tools {
  TOOL_STATE = KEY_ONE,
  TOOL_TRANSITION = KEY_TWO,
};

int main() {
  FiniteAutomaton fa;

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
          fa.add_state(GetMousePosition());
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
          for (size_t i = 0; i < fa.states.size(); i++) {
            std::shared_ptr<State> s = fa.states[i];
            if (CheckCollisionPointCircle(GetMousePosition(), s->position, 20)) {
              fa.remove_state(s);
            }
          }
        }
        break;

      case TOOL_TRANSITION:;
    }

    for (auto s : fa.states) {
      draw_state(*s);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
