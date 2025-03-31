#ifndef _KFLAP_FINITE_AUTOMATON_CORE_H_
#define _KFLAP_FINITE_AUTOMATON_CORE_H_

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class State {
public:
    size_t id;
    std::string name;
    bool final;

    State(size_t id);
};

class Transition {
public:
    std::weak_ptr<State> from;
    std::weak_ptr<State> to;
    char c;

    Transition(std::shared_ptr<State> from, std::shared_ptr<State> to);
};

class FiniteAutomatonCore {
private:
    size_t state_counter;

public:
    std::unordered_map<size_t, std::shared_ptr<State>> states;
    std::unordered_map<size_t, std::vector<size_t>> transitions;

    FiniteAutomatonCore();

    size_t add_state();
    size_t states_count();
    std::optional<std::shared_ptr<State>> get_state(size_t state_id);
    void remove_state(size_t state_id);
    void add_transition(size_t from_id, size_t to_id);
};

#endif /* _KFLAP_FINITE_AUTOMATON_CORE_H_ */
