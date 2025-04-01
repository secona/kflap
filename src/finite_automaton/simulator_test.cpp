#include "finite_automaton/core.h"
#include "finite_automaton/simulator.h"
#include <gtest/gtest.h>

class FiniteAutomatonDFA : public ::testing::Test {
protected:
    FiniteAutomatonCore fac{R"(
<?xml version="1.0" encoding="UTF-8" standalone="no"?><!--Created with JFLAP 7.1.--><structure>
	<type>fa</type>
	<automaton>
		<!--The list of states.-->
		<state id="0" name="q0">
			<x>247.0</x>
			<y>211.0</y>
			<initial/>
		</state>
		<state id="1" name="q1">
			<x>333.0</x>
			<y>34.0</y>
		</state>
		<state id="2" name="q2">
			<x>466.0</x>
			<y>-4.0</y>
		</state>
		<state id="3" name="q3">
			<x>635.0</x>
			<y>40.0</y>
		</state>
		<state id="4" name="q4">
			<x>705.0</x>
			<y>219.0</y>
		</state>
		<state id="5" name="q5">
			<x>573.0</x>
			<y>412.0</y>
		</state>
		<state id="6" name="q6">
			<x>382.0</x>
			<y>413.0</y>
			<final/>
		</state>
		<!--The list of transitions.-->
		<transition>
			<from>0</from>
			<to>0</to>
			<read>a</read>
		</transition>
		<transition>
			<from>6</from>
			<to>6</to>
			<read>a</read>
		</transition>
		<transition>
			<from>3</from>
			<to>0</to>
			<read>a</read>
		</transition>
		<transition>
			<from>0</from>
			<to>0</to>
			<read>b</read>
		</transition>
		<transition>
			<from>6</from>
			<to>6</to>
			<read>b</read>
		</transition>
		<transition>
			<from>4</from>
			<to>5</to>
			<read>a</read>
		</transition>
		<transition>
			<from>1</from>
			<to>2</to>
			<read>b</read>
		</transition>
		<transition>
			<from>1</from>
			<to>1</to>
			<read>c</read>
		</transition>
		<transition>
			<from>6</from>
			<to>6</to>
			<read>c</read>
		</transition>
		<transition>
			<from>5</from>
			<to>0</to>
			<read>a</read>
		</transition>
		<transition>
			<from>3</from>
			<to>4</to>
			<read>c</read>
		</transition>
		<transition>
			<from>3</from>
			<to>2</to>
			<read>b</read>
		</transition>
		<transition>
			<from>0</from>
			<to>1</to>
			<read>c</read>
		</transition>
		<transition>
			<from>2</from>
			<to>0</to>
			<read>b</read>
		</transition>
		<transition>
			<from>2</from>
			<to>3</to>
			<read>c</read>
		</transition>
		<transition>
			<from>5</from>
			<to>6</to>
			<read>b</read>
		</transition>
		<transition>
			<from>1</from>
			<to>0</to>
			<read>a</read>
		</transition>
		<transition>
			<from>2</from>
			<to>0</to>
			<read>a</read>
		</transition>
		<transition>
			<from>5</from>
			<to>1</to>
			<read>c</read>
		</transition>
		<transition>
			<from>4</from>
			<to>2</to>
			<read>b</read>
		</transition>
		<transition>
			<from>4</from>
			<to>1</to>
			<read>c</read>
		</transition>
	</automaton>
</structure>
    )"};
};

TEST_F(FiniteAutomatonDFA, Step)
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

TEST_F(FiniteAutomatonDFA, StepNotInAlphabet)
{
    FiniteAutomatonSimulator fas(fac);

    EXPECT_EQ(fas.get_current_states().size(), 1);

    fas.step('x');
    EXPECT_EQ(fas.get_current_states().size(), 0);
    EXPECT_FALSE(fas.is_accepted());
}
