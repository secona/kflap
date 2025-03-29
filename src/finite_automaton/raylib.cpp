#include "finite_automaton/raylib.h"
#include <raylib.h>
#include <cmath>
#include <numbers>

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
  draw_arrow(t.from->position, t.to->position);
}

void draw_arrow(Vector2 from, Vector2 to) {
  double head_angle = std::numbers::pi / 4;
  double head_length = 15;

  double angle = std::atan2(
    to.y - from.y,
    to.x - from.x
  );

  float left_angle = angle + head_angle;
  float left_x = to.x - std::cos(left_angle) * head_length;
  float left_y = to.y - std::sin(left_angle) * head_length;

  float right_angle = angle - head_angle;
  float right_x = to.x - std::cos(right_angle) * head_length;
  float right_y = to.y - std::sin(right_angle) * head_length;

  DrawLineEx(from, to, 2, BLACK);
  DrawLineEx(to, Vector2{left_x, left_y}, 2, BLACK);
  DrawLineEx(to, Vector2{right_x, right_y}, 2, BLACK);
}
