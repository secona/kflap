#include "finite_automaton/core.h"

#include <cstdlib>
#include <iostream>
#include <optional>
#include <pugixml.hpp>
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

// ============================================================================
// State Constructors
// ============================================================================

State::State(size_t id)
    : id(id)
    , name("q" + std::to_string(id))
    , is_final(false)
{
}

State::State(size_t id, std::string name, bool final)
    : id(id)
    , name(name)
    , is_final(final)
{
}

// ============================================================================
// State Getter Methods
// ============================================================================

const size_t &State::get_id() const
{
    return id;
};

const std::string &State::get_name() const
{
    return name;
};

const bool &State::get_is_final() const
{
    return is_final;
};

// ============================================================================
// FiniteAutomatonCore Constructors
// ============================================================================

FiniteAutomatonCore::FiniteAutomatonCore()
    : state_counter(0)
    , initial_state(-1)
    , states()
    , transitions()
{
}

FiniteAutomatonCore FiniteAutomatonCore::from_jff(std::string filename)
{
    FiniteAutomatonCore fac;

    pugi::xml_document doc;

    if (!doc.load_file(filename.c_str())) {
        std::cerr << "Failed to load_file\n";
        throw 1;
    }

    pugi::xml_node automaton = doc.child("structure").child("automaton");

    for (pugi::xml_node state = automaton.child("state"); state; state = state.next_sibling("state")) {
        size_t state_id = (size_t)state.attribute("id").as_int();
        std::string name = state.attribute("name").as_string();
        bool isfinal = state.child("final");

        fac.add_state(state_id, name, isfinal);

        if (state.child("initial"))
            fac.initial_state = state_id;
    }

    for (pugi::xml_node transition = automaton.child("transition"); transition;
         transition = transition.next_sibling("transition")) {
        size_t from = transition.child("from").text().as_int();
        size_t to = transition.child("to").text().as_int();
        std::string read = transition.child("read").text().as_string();

        fac.add_transition(from, to, read.empty() ? std::nullopt : std::make_optional(read));
    }

    return fac;
}

// ============================================================================
// FiniteAutomatonCore Methods
// ============================================================================

const size_t &FiniteAutomatonCore::get_initial_state() const
{
    return initial_state;
}

const std::unordered_map<size_t, std::shared_ptr<State>> &FiniteAutomatonCore::get_states() const
{
    return states;
}

const std::unordered_map<size_t, std::vector<Transition>> &FiniteAutomatonCore::get_transitions() const
{
    return transitions;
}

size_t FiniteAutomatonCore::add_state()
{
    size_t id = state_counter++;
    auto state = std::make_shared<State>(id);

    states.emplace(id, state);
    transitions.emplace(id, std::vector<Transition>());

    return id;
}

void FiniteAutomatonCore::add_state(size_t id, std::string name, bool final)
{
    auto state = std::make_shared<State>(id, name, final);

    states.emplace(id, state);
    transitions.emplace(id, std::vector<Transition>());
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

void FiniteAutomatonCore::add_transition(size_t from_id, size_t to_id, std::optional<std::string> read)
{
    auto transition = transitions.find(from_id);

    if (transition == transitions.end())
        return;

    transition->second.emplace_back(to_id, read);
}

std::optional<std::vector<Transition>> FiniteAutomatonCore::get_state_transitions(size_t state_id)
{
    auto transition = transitions.find(state_id);

    if (transition == transitions.end())
        return std::nullopt;

    return transition->second;
}

size_t FiniteAutomatonCore::transitions_count()
{
    size_t sum = 0;

    for (const auto &t : transitions)
        sum += t.second.size();

    return sum;
}
