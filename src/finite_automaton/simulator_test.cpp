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
    EXPECT_EQ(fas.current_state, 1);
    EXPECT_FALSE(fas.is_accepted());

    fas.step('b');
    EXPECT_EQ(fas.current_state, 2);
    EXPECT_FALSE(fas.is_accepted());

    fas.reset();
    EXPECT_EQ(fas.current_state, 0);
    EXPECT_FALSE(fas.is_accepted());
}
