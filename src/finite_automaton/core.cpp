#include "finite_automaton/core.h"

#include <optional>
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

// ============================================================================
// State Implementation
// ============================================================================

State::State(size_t id)
    : id(id)
    , name("q" + std::to_string(id))
    , final(false)
{
}

// ============================================================================
// FiniteAutomatonCore Implementation
// ============================================================================

FiniteAutomatonCore::FiniteAutomatonCore()
    : state_counter(0)
    , states()
    , transitions()
{
}

size_t FiniteAutomatonCore::add_state()
{
    size_t id = state_counter++;
    auto state = std::make_shared<State>(id);

    states.emplace(id, state);
    transitions.emplace(id, std::vector<size_t>());

    return id;
}

size_t FiniteAutomatonCore::states_count()
{
    return states.size();
}

std::optional<std::shared_ptr<State>> FiniteAutomatonCore::get_state(size_t state_id)
{
    auto state = states.find(state_id);

    if (state == states.end())
        return std::nullopt;

    return state->second;
}

void FiniteAutomatonCore::remove_state(size_t state_id)
{
    states.erase(state_id);
}

void FiniteAutomatonCore::add_transition(size_t from_id, size_t to_id)
{
    auto transition = transitions.find(from_id);

    if (transition == transitions.end())
        return;

    transition->second.push_back(to_id);
}

std::optional<std::vector<size_t>> FiniteAutomatonCore::get_transitions(size_t state_id)
{
    auto transition = transitions.find(state_id);

    if (transition == transitions.end())
        return std::nullopt;

    return transition->second;
}

size_t FiniteAutomatonCore::transitions_count()
{
    return transitions.size();
}
