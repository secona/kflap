#include "finite_automaton/core.h"

#include <optional>
#include <raylib.h>

#include <memory>
#include <string>

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
}
