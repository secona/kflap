#include "finite_automaton/core.h"
#include "finite_automaton/simulator.h"
#include <gtest/gtest.h>

class FiniteAutomatonSimulatorTests : public ::testing::Test {
protected:
    FiniteAutomatonCore fac = FiniteAutomatonCore::from_jff("examples/DFA.jff");
};

TEST_F(FiniteAutomatonSimulatorTests, Step)
{
    FiniteAutomatonSimulator fas(fac);

    fas.step('c');
    EXPECT_EQ(fas.get_current_states().size(), 1);
    EXPECT_EQ(fas.get_current_states().at(0), 1);
    EXPECT_FALSE(fas.is_accepted());

    fas.step('b');
    EXPECT_EQ(fas.get_current_states().size(), 1);
    EXPECT_EQ(fas.get_current_states().at(0), 2);
    EXPECT_FALSE(fas.is_accepted());

    fas.reset();
    EXPECT_EQ(fas.get_current_states().size(), 1);
    EXPECT_EQ(fas.get_current_states().at(0), 0);
    EXPECT_FALSE(fas.is_accepted());
}

TEST_F(FiniteAutomatonSimulatorTests, StepNotInAlphabet)
{
    FiniteAutomatonSimulator fas(fac);

    EXPECT_EQ(fas.get_current_states().size(), 1);

    fas.step('x');
    EXPECT_EQ(fas.get_current_states().size(), 0);
    EXPECT_FALSE(fas.is_accepted());
}
