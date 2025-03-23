package finiteautomaton

import (
	"math"

	rl "github.com/gen2brain/raylib-go/raylib"
)

const (
	StateState = 1
	StateTransition = 2
	StateMove = 3
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

	moving := false
	var movingState *State

	for !rl.WindowShouldClose() {
		mousePos := rl.GetMousePosition()

		switch st {
		case StateState:
			if rl.IsMouseButtonPressed(rl.MouseLeftButton) {
				fa.AddState(mousePos)
			}

			if rl.IsMouseButtonPressed(rl.MouseRightButton) {
				for _, s := range fa.states {
					if rl.CheckCollisionPointCircle(mousePos, s.Pos, circleRadius) {
						fa.RemoveState(s)
						break
					}
				}
			}

			break

		case StateTransition:
			if rl.IsMouseButtonPressed(rl.MouseLeftButton) {
				for _, s := range fa.states {
					if rl.CheckCollisionPointCircle(mousePos, s.Pos, circleRadius) {
						if !dragging {
							draggingStart = s
						}

						dragging = true

						break
					}
				}
			}

			if rl.IsMouseButtonReleased(rl.MouseLeftButton) {
				for _, s := range fa.states {
					if rl.CheckCollisionPointCircle(mousePos, s.Pos, circleRadius) {
						fa.AddTransition(draggingStart, s)
					}
				}

				dragging = false
			}

			break

		case StateMove:
			if rl.IsMouseButtonPressed(rl.MouseLeftButton) {
				for _, s := range fa.states {
					if rl.CheckCollisionPointCircle(mousePos, s.Pos, circleRadius) {
						if !moving {
							movingState = s
						}

						moving = true

						break
					}
				}
			}

			if rl.IsMouseButtonDown(rl.MouseLeftButton) {
				if moving {
					fa.MoveState(movingState, mousePos)
				}
			}

			if rl.IsMouseButtonReleased(rl.MouseLeftButton) {
				moving = false
				movingState	= nil
			}

			break
		}

		if rl.IsKeyPressed(rl.KeyOne) {
			st = StateState
		}

		if rl.IsKeyPressed(rl.KeyTwo) && !dragging {
			st = StateTransition
		}

		if rl.IsKeyPressed(rl.KeyThree) && !moving {
			st = StateMove 
		}

		rl.BeginDrawing()

		rl.ClearBackground(rl.RayWhite)

		for _, s := range fa.states {
			rl.DrawCircleV(s.Pos, circleRadius, rl.LightGray)
		}

		for i := range fa.transitions {
			t := &fa.transitions[i]
			drawArrow(t.from.Pos, t.to.Pos)
		}

		if dragging {
			drawArrow(draggingStart.Pos, mousePos)
		}

		rl.EndDrawing()
	}
}

func drawArrow(from, to rl.Vector2) {
	headAngle := math.Pi / 4
	headLength := float32(15)
	color := rl.DarkGray

	angle := math.Atan2(float64(to.Y - from.Y), float64(to.X - from.X))

	leftAngle := angle + headAngle
	rightAngle := angle - headAngle

	leftX := to.X - float32(math.Cos(leftAngle)) * headLength
	leftY := to.Y - float32(math.Sin(leftAngle)) * headLength

	rightX := to.X - float32(math.Cos(rightAngle)) * headLength
	rightY := to.Y - float32(math.Sin(rightAngle)) * headLength

	leftPoint := rl.Vector2{X: leftX, Y: leftY}
	rightPoint := rl.Vector2{X: rightX, Y: rightY}

	rl.DrawLineEx(from, to, 2, color)
	rl.DrawLineEx(to, leftPoint, 2, color)
	rl.DrawLineEx(to, rightPoint, 2, color)
}
