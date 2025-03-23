package finiteautomaton

import (
	"math"

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
