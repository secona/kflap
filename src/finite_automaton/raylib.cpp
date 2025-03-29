#include "finite_automaton/raylib.h"
#include <raylib.h>

void draw_state(State state) {
  const int fontSize = 14;

  int textW = MeasureText(state.label.c_str(), fontSize);
  int textH = fontSize;

  int textX = state.position.x - textW / 2;
  int textY = state.position.y - textH / 2;

  DrawCircleV(state.position, 20, LIGHTGRAY);
  DrawText(state.label.c_str(), textX, textY, fontSize, BLACK);
}

void draw_transition(Transition t) {
  DrawLineEx(t.from->position, t.to->position, 2, BLACK);
}
