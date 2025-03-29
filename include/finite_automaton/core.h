#ifndef _KFLAP_FINITE_AUTOMATON_CORE_H_
#define _KFLAP_FINITE_AUTOMATON_CORE_H_

#include <memory>
#include <string>
#include <vector>

class State {
 public:
  std::string label;

  State(size_t);
};

class Transition {
 public:
  std::weak_ptr<State> from;
  std::weak_ptr<State> to;
  char c;

  Transition(std::shared_ptr<State> from, std::shared_ptr<State> to);
};

class FiniteAutomatonCore {
 public:
  std::vector<std::shared_ptr<State>> states;
  std::vector<Transition> transitions;
  size_t state_count;

  FiniteAutomatonCore();
  std::shared_ptr<State> add_state();
  void remove_state(std::shared_ptr<State>);
  void add_transition(std::shared_ptr<State> from, std::shared_ptr<State> to);
};

#endif /* _KFLAP_FINITE_AUTOMATON_CORE_H_ */
