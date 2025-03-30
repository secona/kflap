#ifndef _KFLAP_FINITE_AUTOMATON_RENDERER_H_
#define _KFLAP_FINITE_AUTOMATON_RENDERER_H_

#include <raylib.h>

#include <optional>
#include <unordered_map>

#include "finite_automaton/core.h"

enum Tools {
    TOOL_STATE = KEY_ONE,
    TOOL_TRANSITION = KEY_TWO,
    TOOL_MOVE = KEY_THREE,
};

class FiniteAutomatonCanvas {
public:
    FiniteAutomatonCanvas();
    void run();
    void draw();

private:
    std::unordered_map<std::shared_ptr<State>, Vector2> state_positions;
    std::optional<std::shared_ptr<State>> transition_from;
    std::optional<std::shared_ptr<State>> moving_state;

    Tools tool;
    FiniteAutomatonCore fa;

    void draw_state(std::shared_ptr<State> state);
    void draw_transition(Transition);
};

#endif /* _KFLAP_FINITE_AUTOMATON_RENDERER_H_ */
