#ifndef _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_
#define _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_

#include "finite_automaton/core.h"
#include <vector>

class FiniteAutomatonSimulator {
private:
    const FiniteAutomatonCore &fac;
    std::vector<size_t> current_states;

public:
    // =========================================================================
    // Constructors
    // =========================================================================

    FiniteAutomatonSimulator(const FiniteAutomatonCore &fac);

    // =========================================================================
    // Getter Methods
    // =========================================================================

    const std::vector<size_t> &get_current_states() const;

    // =========================================================================
    // Simulator Methods
    // =========================================================================

    void step(char ch);
    void reset();
    bool is_accepted();
};

#endif /* _KFLAP_FINITE_AUTOMATON_SIMULATOR_H_ */
