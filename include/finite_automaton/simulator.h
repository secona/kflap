#ifndef _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_
#define _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_

#include "finite_automaton/core.h"

class FiniteAutomatonSimulator {
private:
    const FiniteAutomatonCore &fac;
    size_t current_state;

public:
    // =========================================================================
    // Constructors
    // =========================================================================

    FiniteAutomatonSimulator(const FiniteAutomatonCore &fac);

    // =========================================================================
    // Getter Methods
    // =========================================================================

    const State &get_current_state() const;

    // =========================================================================
    // Simulator Methods
    // =========================================================================

    void step(char ch);
    void reset();
    bool is_accepted();
};

#endif /* _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_ */
