#ifndef _KFLAP_FINITE_AUTOMATON_CORE_H_
#define _KFLAP_FINITE_AUTOMATON_CORE_H_

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class State {
public:
    size_t id;
    std::string name;
    bool final;

    State(size_t id);
    State(size_t id, std::string name, bool final);
};

class FiniteAutomatonCore {
private:
    size_t state_counter;
    size_t initial_state;

    std::unordered_map<size_t, std::shared_ptr<State>> states;
    std::unordered_map<size_t, std::vector<std::pair<size_t, char>>> transitions;

public:
    // =========================================================================
    // Constructors
    // =========================================================================

    FiniteAutomatonCore();
    static FiniteAutomatonCore from_jff(std::string filename);

    // =========================================================================
    // Getter Methods
    // =========================================================================

    const size_t &get_initial_state() const;
    const std::unordered_map<size_t, std::shared_ptr<State>> &get_states() const;
    const std::unordered_map<size_t, std::vector<std::pair<size_t, char>>> &get_transitions() const;

    // =========================================================================
    // State Management Methods
    // =========================================================================

    size_t add_state();
    void add_state(size_t id, std::string name, bool final);
    size_t states_count();
    std::optional<std::shared_ptr<State>> get_state(size_t state_id);
    void remove_state(size_t state_id);

    // =========================================================================
    // Transition Management Methods
    // =========================================================================

    void add_transition(size_t from_id, size_t to_id, char c);
    std::optional<std::vector<std::pair<size_t, char>>> get_transitions(size_t state_id);
    size_t transitions_count();
};

#endif /* _KFLAP_FINITE_AUTOMATON_CORE_H_ */
