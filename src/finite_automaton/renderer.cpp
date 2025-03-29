#include "finite_automaton/renderer.h"
#include "finite_automaton/raylib.h"
#include "finite_automaton/core.h"

FiniteAutomatonRenderer::FiniteAutomatonRenderer()
    : transition_from(), moving_state(), fa() {}

void FiniteAutomatonRenderer::run() {
  if (IsKeyPressed(TOOL_STATE)) tool = TOOL_STATE;
  if (IsKeyPressed(TOOL_TRANSITION)) tool = TOOL_TRANSITION;
  if (IsKeyPressed(TOOL_MOVE)) tool = TOOL_MOVE;

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

    case TOOL_TRANSITION:
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (size_t i = 0; i < fa.states.size(); i++) {
          std::shared_ptr<State> s = fa.states[i];
          if (CheckCollisionPointCircle(GetMousePosition(), s->position, 20)) {
            transition_from = s;
          }
        }
      }

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (transition_from.has_value())
          for (size_t i = 0; i < fa.states.size(); i++) {
            std::shared_ptr<State> s = fa.states[i];
            if (CheckCollisionPointCircle(GetMousePosition(), s->position, 20)) {
              fa.add_transition(transition_from.value(), s);
            }
          }

        transition_from.reset();
      }

      if (transition_from.has_value()) {
        State start = *transition_from.value();
        draw_arrow(start.position, GetMousePosition());
      }

      break;

    case TOOL_MOVE:
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (size_t i = 0; i < fa.states.size(); i++) {
          std::shared_ptr<State> s = fa.states[i];
          if (CheckCollisionPointCircle(GetMousePosition(), s->position, 20)) {
            moving_state = s;
          }
        }
      }

      if (moving_state.has_value()) {
        moving_state->get()->position = GetMousePosition();
      }

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        moving_state.reset();
      }

      break;
  }

  for (auto s : fa.states) {
    draw_state(*s);
  }

  for (auto t = fa.transitions.begin(); t != fa.transitions.end();) {
    if (!t->to.expired() && !t->from.expired()) {
      draw_transition(*t);
      ++t;
    } else {
      t = fa.transitions.erase(t);
    }
  }

  EndDrawing();
}
