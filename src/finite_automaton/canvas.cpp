#include "finite_automaton/canvas.h"

#include <raylib.h>

#include <cmath>

#include "finite_automaton/core.h"

void FiniteAutomatonCanvas::draw_state(std::shared_ptr<State> state) {
  const int fontSize = 14;
  Vector2 position = state_positions[state];

  float textW = MeasureText(state->label.c_str(), fontSize);
  float textH = fontSize;

  int textX = position.x - textW / 2;
  int textY = position.y - textH / 2;

  DrawCircleV(position, 20, LIGHTGRAY);
  DrawText(state->label.c_str(), textX, textY, fontSize, BLACK);
}

void draw_arrow(Vector2 from, Vector2 to) {
  double head_angle = std::numbers::pi / 4;
  double head_length = 15;

  double angle = std::atan2(to.y - from.y, to.x - from.x);

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

void FiniteAutomatonCanvas::draw_transition(Transition t) {
  Vector2 from = state_positions[t.from.lock()];
  Vector2 to = state_positions[t.to.lock()];

  draw_arrow(from, to);

  char text[] = {t.c, 0};
  DrawText(text, from.x + (to.x - from.x) / 2, from.y + (to.y - from.y) / 2, 14,
           BLACK);
}

FiniteAutomatonCanvas::FiniteAutomatonCanvas()
    : state_positions(), transition_from(), moving_state(), fa() {}

void FiniteAutomatonCanvas::run() {
  if (IsKeyPressed(TOOL_STATE)) tool = TOOL_STATE;
  if (IsKeyPressed(TOOL_TRANSITION)) tool = TOOL_TRANSITION;
  if (IsKeyPressed(TOOL_MOVE)) tool = TOOL_MOVE;

  BeginDrawing();

  ClearBackground(RAYWHITE);

  switch (tool) {
    case TOOL_STATE:
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::shared_ptr<State> state = fa.add_state();
        state_positions[state] = GetMousePosition();
      }

      if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        for (size_t i = 0; i < fa.states.size(); i++) {
          std::shared_ptr<State> s = fa.states[i];
          if (CheckCollisionPointCircle(GetMousePosition(), state_positions[s],
                                        20)) {
            fa.remove_state(s);
            state_positions.erase(s);
          }
        }
      }
      break;

    case TOOL_TRANSITION:
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (size_t i = 0; i < fa.states.size(); i++) {
          std::shared_ptr<State> s = fa.states[i];
          if (CheckCollisionPointCircle(GetMousePosition(), state_positions[s],
                                        20)) {
            transition_from = s;
          }
        }
      }

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (transition_from.has_value())
          for (size_t i = 0; i < fa.states.size(); i++) {
            std::shared_ptr<State> s = fa.states[i];
            if (CheckCollisionPointCircle(GetMousePosition(),
                                          state_positions[s], 20)) {
              fa.add_transition(transition_from.value(), s);
            }
          }

        transition_from.reset();
      }

      if (transition_from.has_value()) {
        draw_arrow(state_positions[*transition_from], GetMousePosition());
      }

      break;

    case TOOL_MOVE:
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (size_t i = 0; i < fa.states.size(); i++) {
          std::shared_ptr<State> s = fa.states[i];
          if (CheckCollisionPointCircle(GetMousePosition(), state_positions[s],
                                        20)) {
            moving_state = s;
          }
        }
      }

      if (moving_state.has_value()) {
        state_positions[*moving_state] = GetMousePosition();
      }

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        moving_state.reset();
      }

      break;
  }

  draw();

  EndDrawing();
}

void FiniteAutomatonCanvas::draw() {
  for (auto s : fa.states) {
    draw_state(s);
  }

  for (auto t = fa.transitions.begin(); t != fa.transitions.end();) {
    if (!t->to.expired() && !t->from.expired()) {
      draw_transition(*t);
      ++t;
    } else {
      t = fa.transitions.erase(t);
    }
  }
}
