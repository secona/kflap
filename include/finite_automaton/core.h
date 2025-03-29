#ifndef _KFLAP_FINITE_AUTOMATON_CORE_H_
#define _KFLAP_FINITE_AUTOMATON_CORE_H_

#include <raylib.h>

#include <string>
#include <memory>
#include <vector>

class State {
 public:
  std::string label;
  Vector2 position;

  State(size_t, Vector2);
};

class FiniteAutomaton {
 public:
  std::vector<std::shared_ptr<State>> states;
  size_t state_count;

  FiniteAutomaton();
  void add_state(Vector2 position);
  void remove_state(std::shared_ptr<State>);
};

#endif /* _KFLAP_FINITE_AUTOMATON_CORE_H_ */
