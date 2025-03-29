#ifndef _KFLAP_FINITE_AUTOMATON_RENDERER_H_
#define _KFLAP_FINITE_AUTOMATON_RENDERER_H_

#include <raylib.h>

#include "finite_automaton/core.h"

#include <optional>
#include <memory>

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
  std::optional<std::shared_ptr<State>> transition_from = std::nullopt;
  std::optional<std::shared_ptr<State>> moving_state = std::nullopt;
  Tools tool = TOOL_STATE;
  FiniteAutomaton fa;
};

#endif /* _KFLAP_FINITE_AUTOMATON_RENDERER_H_ */
