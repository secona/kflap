#include "finite_automaton/core.h"
#include <gtest/gtest.h>
#include <optional>

class FiniteAutomatonTests : public ::testing::Test {
protected:
    FiniteAutomatonCore fac;
};

TEST_F(FiniteAutomatonTests, AddState)
{
    size_t state_id1 = fac.add_state();
    auto state1 = fac.get_state(state_id1);
    EXPECT_EQ(state1->get()->id, 0);

    size_t state_id2 = fac.add_state();
    auto state2 = fac.get_state(state_id2);
    EXPECT_EQ(state2->get()->id, 1);

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
    EXPECT_EQ(state1->get()->id, 0);

    size_t state_id2 = fac.add_state();
    auto state2 = fac.get_state(state_id2);
    EXPECT_EQ(state2->get()->id, 1);

    fac.add_transition(state_id1, state_id2, "a");
    auto transitions = fac.get_state_transitions(state_id1);
    EXPECT_EQ(transitions->size(), 1);
    EXPECT_EQ(transitions->at(0).state_id, state_id2);
    EXPECT_EQ(transitions->at(0).read, "a");
}

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

TEST_F(FiniteAutomatonDFA, CanParseJFF)
{
    EXPECT_EQ(fac.get_initial_state(), 0);
    EXPECT_EQ(fac.states_count(), 7);
    EXPECT_EQ(fac.transitions_count(), 21);
}

class FiniteAutomatonNDFA : public ::testing::Test {
protected:
    FiniteAutomatonCore fac{R"(
<?xml version="1.0" encoding="UTF-8" standalone="no"?><!--Created with JFLAP 7.1.--><structure>
  <type>fa</type>
  <automaton>
    <!--The list of states.-->
    <state id="0" name="q0">
      <x>301.0</x>
      <y>393.0</y>
    </state>
    <state id="1" name="q1">
      <x>368.0</x>
      <y>492.0</y>
    </state>
    <state id="2" name="q2">
      <x>510.0</x>
      <y>489.0</y>
    </state>
    <state id="3" name="q3">
      <x>615.0</x>
      <y>591.0</y>
    </state>
    <state id="4" name="q4">
      <x>757.0</x>
      <y>592.0</y>
    </state>
    <state id="5" name="q5">
      <x>907.0</x>
      <y>490.0</y>
    </state>
    <state id="6" name="q6">
      <x>1053.0</x>
      <y>493.0</y>
      <final/>
    </state>
    <state id="7" name="q7">
      <x>219.0</x>
      <y>393.0</y>
      <initial/>
      <final/>
    </state>
    <state id="8" name="q8">
      <x>360.0</x>
      <y>293.0</y>
    </state>
    <state id="9" name="q9">
      <x>481.0</x>
      <y>288.0</y>
    </state>
    <state id="10" name="q10">
      <x>573.0</x>
      <y>289.0</y>
    </state>
    <state id="11" name="q11">
      <x>572.0</x>
      <y>228.0</y>
    </state>
    <state id="12" name="q12">
      <x>667.0</x>
      <y>289.0</y>
    </state>
    <state id="13" name="q13">
      <x>664.0</x>
      <y>227.0</y>
    </state>
    <state id="14" name="q14">
      <x>779.0</x>
      <y>227.0</y>
    </state>
    <state id="15" name="q15">
      <x>880.0</x>
      <y>232.0</y>
    </state>
    <state id="16" name="q16">
      <x>981.0</x>
      <y>237.0</y>
    </state>
    <state id="17" name="q17">
      <x>774.0</x>
      <y>291.0</y>
    </state>
    <state id="18" name="q18">
      <x>1058.0</x>
      <y>288.0</y>
      <final/>
    </state>
    <!--The list of transitions.-->
    <transition>
      <from>9</from>
      <to>11</to>
      <read/>
    </transition>
    <transition>
      <from>16</from>
      <to>18</to>
      <read>c</read>
    </transition>
    <transition>
      <from>17</from>
      <to>18</to>
      <read>c</read>
    </transition>
    <transition>
      <from>12</from>
      <to>17</to>
      <read/>
    </transition>
    <transition>
      <from>3</from>
      <to>4</to>
      <read>b</read>
    </transition>
    <transition>
      <from>1</from>
      <to>2</to>
      <read>a</read>
    </transition>
    <transition>
      <from>7</from>
      <to>0</to>
      <read/>
    </transition>
    <transition>
      <from>13</from>
      <to>14</to>
      <read/>
    </transition>
    <transition>
      <from>4</from>
      <to>5</to>
      <read/>
    </transition>
    <transition>
      <from>6</from>
      <to>0</to>
      <read/>
    </transition>
    <transition>
      <from>14</from>
      <to>15</to>
      <read>b</read>
    </transition>
    <transition>
      <from>2</from>
      <to>5</to>
      <read/>
    </transition>
    <transition>
      <from>0</from>
      <to>1</to>
      <read/>
    </transition>
    <transition>
      <from>10</from>
      <to>12</to>
      <read>c</read>
    </transition>
    <transition>
      <from>4</from>
      <to>3</to>
      <read/>
    </transition>
    <transition>
      <from>2</from>
      <to>3</to>
      <read/>
    </transition>
    <transition>
      <from>15</from>
      <to>16</to>
      <read/>
    </transition>
    <transition>
      <from>5</from>
      <to>6</to>
      <read>c</read>
    </transition>
    <transition>
      <from>2</from>
      <to>1</to>
      <read/>
    </transition>
    <transition>
      <from>9</from>
      <to>10</to>
      <read/>
    </transition>
    <transition>
      <from>0</from>
      <to>5</to>
      <read/>
    </transition>
    <transition>
      <from>0</from>
      <to>8</to>
      <read/>
    </transition>
    <transition>
      <from>8</from>
      <to>9</to>
      <read>b</read>
    </transition>
    <transition>
      <from>18</from>
      <to>0</to>
      <read/>
    </transition>
    <transition>
      <from>0</from>
      <to>3</to>
      <read/>
    </transition>
    <transition>
      <from>11</from>
      <to>13</to>
      <read>a</read>
    </transition>
  </automaton>
</structure>
    )"};
};

TEST_F(FiniteAutomatonNDFA, CanParseJFFLambdaTransitions)
{
    auto transitions = fac.get_state_transitions(9).value();

    for (const auto &t : transitions) {
        EXPECT_EQ(t.read, std::nullopt);
    }
}
