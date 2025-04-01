#include "finite_automaton/simulator.h"
#include "finite_automaton/core.h"
#include <vector>

// ============================================================================
// Constructors
// ============================================================================

FiniteAutomatonSimulator::FiniteAutomatonSimulator(const FiniteAutomatonCore &fac)
    : fac(fac)
    , current_states(1, fac.get_initial_state())
{
}

// ============================================================================
// Getter Methods
// ============================================================================

const std::vector<size_t> &FiniteAutomatonSimulator::get_current_states() const
{
    return current_states;
}

// ============================================================================
// Simulator Methods
// ============================================================================

void FiniteAutomatonSimulator::step(char ch)
{
    std::vector<size_t> new_states;
    auto transitions = fac.get_transitions();

    for (const auto &s : current_states) {
        for (const auto &[state_id, c] : transitions[s]) {
            if (ch == c) {
                new_states.push_back(state_id);
            }
        }
    }

    current_states = new_states;
}

bool FiniteAutomatonSimulator::is_accepted()
{
    auto states = fac.get_states();

    for (const auto& state_id : current_states) {
        if (states.at(state_id)->final)
            return true;
    }

    return false;
}

void FiniteAutomatonSimulator::reset()
{
    current_states = {fac.get_initial_state()};
}
