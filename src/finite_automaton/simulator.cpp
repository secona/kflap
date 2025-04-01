#include "finite_automaton/core.h"
#include "finite_automaton/simulator.h"

FiniteAutomatonSimulator::FiniteAutomatonSimulator(FiniteAutomatonCore&& fac)
	: fac(std::move(fac))
	, current_state(fac.get_initial_state())
{
}

void FiniteAutomatonSimulator::step(char ch)
{
	for (const auto& [state_id, c] : fac.transitions[current_state]) {
		if (ch == c) {
			current_state = state_id;
			break;
		}
	}
}

bool FiniteAutomatonSimulator::is_accepted()
{
	return fac.states[current_state]->final;
}

void FiniteAutomatonSimulator::reset()
{
	current_state = fac.get_initial_state();
}
