package finiteautomaton

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

const (
	StateState = 1
	StateTransition = 2
)

func Run() {
	rl.SetConfigFlags(rl.FlagWindowResizable)
	rl.SetTargetFPS(60)

	rl.InitWindow(800, 450, "kflap")
	defer rl.CloseWindow()

	fa := NewAutomaton()
	st := StateState

	circleRadius := float32(20)

	dragging := false
	var draggingStart *State

	for !rl.WindowShouldClose() {
		mousePos := rl.GetMousePosition()

		switch st {
		case StateState:
			if rl.IsMouseButtonPressed(rl.MouseLeftButton) {
				fa.AddState(mousePos)
			}

			if rl.IsMouseButtonPressed(rl.MouseRightButton) {
				for s := range fa.States {
					if rl.CheckCollisionPointCircle(mousePos, s.Pos, circleRadius) {
						fa.RemoveState(s)
						break
					}
				}
			}

			break

		case StateTransition:
			if rl.IsMouseButtonDown(rl.MouseLeftButton) {
				for s := range fa.States {
					if rl.CheckCollisionPointCircle(mousePos, s.Pos, circleRadius) {
						if !dragging {
							draggingStart = &s
						}

						dragging = true

						break
					}
				}
			}

			if rl.IsMouseButtonReleased(rl.MouseLeftButton) {
				for s := range fa.States {
					if rl.CheckCollisionPointCircle(mousePos, s.Pos, circleRadius) {
						fa.AddTransition(draggingStart, &s)
					}
				}

				dragging = false
			}
		}

		if rl.IsKeyPressed(rl.KeyOne) {
			st = StateState
		}

		if rl.IsKeyPressed(rl.KeyTwo) && !dragging {
			st = StateTransition
		}

		rl.BeginDrawing()

		rl.ClearBackground(rl.RayWhite)

		for s := range fa.States {
			rl.DrawCircleV(s.Pos, circleRadius, rl.LightGray)
		}

		for t := range fa.Transitions {
			rl.DrawLineEx(t.from.Pos, t.to.Pos, 2, rl.LightGray)
		}

		if dragging {
			rl.DrawLineEx(draggingStart.Pos, mousePos, 2, rl.LightGray)
		}

		rl.EndDrawing()
	}
}
