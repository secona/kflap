package finiteautomaton

import (
	"fmt"
	rl "github.com/gen2brain/raylib-go/raylib"
)

type State struct {
	Label string
	Pos   rl.Vector2
}

type Transition struct {
	from *State
	to   *State
}

type FiniteAutomaton struct {
	states      []*State
	transitions []Transition

	stateCount int
}

func NewAutomaton() *FiniteAutomaton {
	return &FiniteAutomaton{
		states:      make([]*State, 0),
		transitions: make([]Transition, 0),

		stateCount: 0,
	}
}

func (fa *FiniteAutomaton) AddState(pos rl.Vector2) {
	s := &State{
		Label: fmt.Sprint(fa.stateCount),
		Pos:   pos,
	}

	fa.states = append(fa.states, s)
	fa.stateCount++
}

func (fa *FiniteAutomaton) AddTransition(start *State, to *State) {
	t := Transition{start, to}

	fa.transitions = append(fa.transitions, t)
}

func (fa *FiniteAutomaton) RemoveState(s *State) {
	newStates := []*State{}
	newTransitions := []Transition{}

	for _, state := range fa.states {
		if s != state {
			newStates = append(newStates, state)
		}
	}

	for _, t := range fa.transitions {
		if t.from != s && t.to != s {
			newTransitions = append(newTransitions, t)
		}
	}

	fa.states = newStates
	fa.transitions = newTransitions
}

func (fa *FiniteAutomaton) RemoveTransition() {

}

func (fa *FiniteAutomaton) MoveState(s *State, p rl.Vector2) {
	(*s).Pos.X = p.X
	(*s).Pos.Y = p.Y
}
