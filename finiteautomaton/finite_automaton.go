package finiteautomaton

import (
	"fmt"
	rl "github.com/gen2brain/raylib-go/raylib"
)

type State struct {
	Label string
	Pos	  rl.Vector2
}

type Transition struct {
	from *State
	to *State
}

type FiniteAutomaton struct {
	states []State
	transitions []Transition

	stateCount int
}

func NewAutomaton() *FiniteAutomaton {
	return &FiniteAutomaton{
		states: make([]State, 0),
		transitions: make([]Transition, 0),

		stateCount: 0,
	}
}

func (fa *FiniteAutomaton) States(yield func(State) bool) {
	for _, s := range fa.states {
		if !yield(s) {
			return
		}
	}
}

func (fa *FiniteAutomaton) AddState(pos rl.Vector2) {
	s := State {
		Label: fmt.Sprint(fa.stateCount),
		Pos: pos,
	}

	fa.states = append(fa.states, s)
	fa.stateCount++;
}

func (fa *FiniteAutomaton) AddTransition() {

}

func (fa *FiniteAutomaton) RemoveState(s State) {
	newStates := []State{}

	for _, state := range fa.states {
		if s != state {
			newStates = append(newStates, state);
		}
	}

	fa.states = newStates
}

func (fa *FiniteAutomaton) RemoveTransition() {

}
