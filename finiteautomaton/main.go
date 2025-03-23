package finiteautomaton

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

func Run() {
	rl.SetConfigFlags(rl.FlagWindowResizable)
	rl.SetTargetFPS(60)

	rl.InitWindow(800, 450, "kflap")
	defer rl.CloseWindow()

	fa := NewAutomaton()

	circleRadius := float32(20)

	for !rl.WindowShouldClose() {
		mousePos := rl.GetMousePosition()

		if rl.IsMouseButtonPressed(rl.MouseLeftButton) {
			fa.AddState(mousePos)
		}

		// if rl.IsMouseButtonPressed(rl.MouseRightButton) {
		// 	for i := 0; i < len(circles); i++ {
		// 		if rl.CheckCollisionPointCircle(mousePos, circles[i], circleRadius) {
		// 			// Remove circle
		// 			circles = append(circles[:i], circles[i+1:]...)
		// 			break // Stop after removing one
		// 		}
		// 	}
		// }

		rl.BeginDrawing()

		rl.ClearBackground(rl.RayWhite)

		for s := range fa.States {
			rl.DrawCircleV(s.Pos, circleRadius, rl.LightGray)
		}

		rl.EndDrawing()
	}
}
