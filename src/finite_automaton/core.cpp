#include "finite_automaton/core.h"
#include <raylib.h>
#include <string>

State::State(size_t number, Vector2 position): position(position) {
	label = "q" + std::to_string(number);
}
