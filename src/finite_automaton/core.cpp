#include "finite_automaton/core.h"

#include <raylib.h>

#include <algorithm>
#include <memory>
#include <string>

State::State(size_t number, Vector2 position) : position(position) {
  label = "q" + std::to_string(number);
}

Transition::Transition(std::shared_ptr<State> from, std::shared_ptr<State> to) : from(from), to(to) {}

FiniteAutomaton::FiniteAutomaton(): states(), transitions(), state_count(0) {}

void FiniteAutomaton::add_state(Vector2 position) {
  State state(state_count, position);
  states.emplace_back(std::make_shared<State>(state));
  state_count++;
}

void FiniteAutomaton::remove_state(std::shared_ptr<State> state) {
  states.erase(std::remove(states.begin(), states.end(), state), states.end());
}

void FiniteAutomaton::add_transition(std::shared_ptr<State> from, std::shared_ptr<State> to) {
  transitions.emplace_back(from, to);
}
