#include "finite_automaton/canvas.h"

// #include <algorithm>
#include <optional>
#include <raylib.h>

#include <cmath>

#include "finite_automaton/core.h"

// ============================================================================
// CONSTANT VARIABLES
// ============================================================================

constexpr int FONT_SIZE = 14;

constexpr float ARROW_HEAD_ANGLE = std::numbers::pi / 4;
constexpr int ARROW_HEAD_LENGTH = 15;

constexpr int STATE_RADIUS = 20;
constexpr Color STATE_COLOR = LIGHTGRAY;
constexpr Color STATE_TEXT_COLOR = BLACK;

// ============================================================================
// GENERAL DRAWING FUNCTIONS
// ============================================================================

void draw_arrow(Vector2 from, Vector2 to)
{
    double angle = std::atan2(to.y - from.y, to.x - from.x);

    Vector2 left = {
        static_cast<float>(to.x - std::cos(angle + ARROW_HEAD_ANGLE) * ARROW_HEAD_LENGTH),
        static_cast<float>(to.y - std::sin(angle + ARROW_HEAD_ANGLE) * ARROW_HEAD_LENGTH),
    };

    Vector2 right = {
        static_cast<float>(to.x - std::cos(angle - ARROW_HEAD_ANGLE) * ARROW_HEAD_LENGTH),
        static_cast<float>(to.y - std::sin(angle - ARROW_HEAD_ANGLE) * ARROW_HEAD_LENGTH),
    };

    DrawLineEx(from, to, 2, BLACK);
    DrawLineEx(to, left, 2, BLACK);
    DrawLineEx(to, right, 2, BLACK);
}

// ============================================================================
// FiniteAutomatonCanvas DRAWING FUNCTIONS
// ============================================================================

void FiniteAutomatonCanvas::draw()
{
    for (auto s : fa.states) {
        // draw_state(s);
    }

    // fa.transitions.erase(std::remove_if(fa.transitions.begin(),
    //                                     fa.transitions.end(),
    //                                     [this](const Transition &t) {
    //                                         if (t.to.expired() || t.from.expired())
    //                                             return true;
    //                                         draw_transition(t);
    //                                         return false;
    //                                     }),
    //                      fa.transitions.end());
}

void FiniteAutomatonCanvas::draw_state(std::shared_ptr<State> state)
{
    Vector2 position = state_positions[state];

    float textW = MeasureText(state->name.c_str(), FONT_SIZE);
    float textH = FONT_SIZE;

    int textX = position.x - textW / 2;
    int textY = position.y - textH / 2;

    DrawCircleV(position, STATE_RADIUS, STATE_COLOR);
    DrawText(state->name.c_str(), textX, textY, FONT_SIZE, STATE_TEXT_COLOR);
}

void FiniteAutomatonCanvas::draw_transition(Transition t)
{
    Vector2 from = state_positions[t.from.lock()];
    Vector2 to = state_positions[t.to.lock()];

    draw_arrow(from, to);

    char text[] = {t.c, 0};
    DrawText(text, from.x + (to.x - from.x) / 2, from.y + (to.y - from.y) / 2, 14, BLACK);
}

// ============================================================================
// START OF FiniteAutomatonCanvas IMPLEMENTATION
// ============================================================================

FiniteAutomatonCanvas::FiniteAutomatonCanvas()
    : state_positions()
    , transition_from(std::nullopt)
    , moving_state(std::nullopt)
    , tool(TOOL_STATE)
    , fa()
{
}

void FiniteAutomatonCanvas::run()
{
    if (IsKeyPressed(TOOL_STATE))
        tool = TOOL_STATE;
    if (IsKeyPressed(TOOL_TRANSITION))
        tool = TOOL_TRANSITION;
    if (IsKeyPressed(TOOL_MOVE))
        tool = TOOL_MOVE;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (tool) {
    case TOOL_STATE:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // std::shared_ptr<State> state = fa.add_state();
            // state_positions[state] = GetMousePosition();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            // for (auto &s : fa.states) {
            //     if (CheckCollisionPointCircle(GetMousePosition(), state_positions[s], 20)) {
            //         fa.remove_state(s);
            //         state_positions.erase(s);
            //     }
            // }
        }
        break;

    case TOOL_TRANSITION:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // for (auto &s : fa.states) {
            //     if (CheckCollisionPointCircle(GetMousePosition(), state_positions[s], 20)) {
            //         transition_from = s;
            //     }
            // }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (transition_from.has_value())
                // for (auto &s : fa.states) {
                //     if (CheckCollisionPointCircle(GetMousePosition(), state_positions[s], 20)) {
                //         fa.add_transition(transition_from.value(), s);
                //     }
                // }

                transition_from.reset();
        }

        if (transition_from.has_value()) {
            draw_arrow(state_positions[*transition_from], GetMousePosition());
        }

        break;

    case TOOL_MOVE:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // for (auto &s : fa.states) {
            //     if (CheckCollisionPointCircle(GetMousePosition(), state_positions[s], 20)) {
            //         moving_state = s;
            //     }
            // }
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
