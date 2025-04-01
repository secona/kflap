#ifndef _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_
#define _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_

#include "finite_automaton/core.h"

class FiniteAutomatonSimulator {
public:
    FiniteAutomatonCore fac;
    size_t current_state;

    FiniteAutomatonSimulator(const FiniteAutomatonCore &fac);

    void step(char ch);
    void reset();
    bool is_accepted();
};

#endif /* _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_ */
