#include "finite_automaton/core.h"

#include <raylib.h>

#include <algorithm>
#include <memory>
#include <string>

State::State(size_t number) : label("q" + std::to_string(number)) {}

Transition::Transition(std::shared_ptr<State> from, std::shared_ptr<State> to)
    : from(from), to(to), c('a') {}

FiniteAutomatonCore::FiniteAutomatonCore() : states(), transitions(), state_count(0) {}

std::shared_ptr<State> FiniteAutomatonCore::add_state() {
  auto state = std::make_shared<State>(state_count++);
  states.emplace_back(state);

  return state;
}

void FiniteAutomatonCore::remove_state(std::shared_ptr<State> state) {
  states.erase(std::remove(states.begin(), states.end(), state), states.end());
}

void FiniteAutomatonCore::add_transition(std::shared_ptr<State> from,
                                     std::shared_ptr<State> to) {
  transitions.emplace_back(from, to);
}
