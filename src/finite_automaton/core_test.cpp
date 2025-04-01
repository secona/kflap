#include "finite_automaton/core.h"
#include <gtest/gtest.h>

class FiniteAutomatonTests : public ::testing::Test {
protected:
    FiniteAutomatonCore fac;
};

TEST_F(FiniteAutomatonTests, AddState)
{
    size_t state_id1 = fac.add_state();
    auto state1 = fac.get_state(state_id1);
    EXPECT_EQ(state1->get()->get_id(), 0);

    size_t state_id2 = fac.add_state();
    auto state2 = fac.get_state(state_id2);
    EXPECT_EQ(state2->get()->get_id(), 1);

    EXPECT_EQ(fac.states_count(), 2);
}

TEST_F(FiniteAutomatonTests, InvalidGetState)
{
    auto state = fac.get_state(999);
    EXPECT_EQ(state, std::nullopt);
}

TEST_F(FiniteAutomatonTests, RemoveState)
{
    size_t state_id1 = fac.add_state();
    EXPECT_EQ(fac.states_count(), 1);

    fac.remove_state(state_id1);
    EXPECT_EQ(fac.states_count(), 0);

    size_t state_id2 = fac.add_state();
    EXPECT_EQ(state_id2, 1);

    fac.remove_state(state_id1);
    EXPECT_EQ(fac.states_count(), 1);
}

TEST_F(FiniteAutomatonTests, AddTransition)
{
    size_t state_id1 = fac.add_state();
    auto state1 = fac.get_state(state_id1);
    EXPECT_EQ(state1->get()->get_id(), 0);

    size_t state_id2 = fac.add_state();
    auto state2 = fac.get_state(state_id2);
    EXPECT_EQ(state2->get()->get_id(), 1);

    fac.add_transition(state_id1, state_id2, 'a');
    auto transitions = fac.get_state_transitions(state_id1);
    EXPECT_EQ(transitions->size(), 1);
    EXPECT_EQ(transitions->at(0).state_id, state_id2);
    EXPECT_EQ(transitions->at(0).read, 'a');
}

TEST(FiniteAutomatonJFF, CanParseJFF)
{
    FiniteAutomatonCore fac = FiniteAutomatonCore::from_jff("examples/DFA.jff");
    EXPECT_EQ(fac.get_initial_state(), 0);
    EXPECT_EQ(fac.states_count(), 7);
    EXPECT_EQ(fac.transitions_count(), 21);
}
