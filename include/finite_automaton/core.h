#ifndef _KFLAP_FINITE_AUTOMATON_CORE_H_
#define _KFLAP_FINITE_AUTOMATON_CORE_H_

#include <string>
#include <raylib.h>

class State {
public:
	std::string label;
	Vector2 position;

	State(size_t, Vector2);
};

#endif /* _KFLAP_FINITE_AUTOMATON_CORE_H_ */
