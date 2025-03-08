package main

import (
	rg "github.com/gen2brain/raylib-go/raygui"
	rl "github.com/gen2brain/raylib-go/raylib"
)

func main() {
	rl.SetConfigFlags(rl.FlagWindowResizable)
	rl.SetTargetFPS(60)

	rl.InitWindow(800, 450, "kflap")
	defer rl.CloseWindow()

	var circles []rl.Vector2
	circleRadius := float32(20)

	for !rl.WindowShouldClose() {
		mousePos := rl.GetMousePosition()

		if rl.IsMouseButtonPressed(rl.MouseLeftButton) {
			circles = append(circles, mousePos)
		}

		if rl.IsMouseButtonPressed(rl.MouseRightButton) {
			for i := 0; i < len(circles); i++ {
				if rl.CheckCollisionPointCircle(mousePos, circles[i], circleRadius) {
					// Remove circle
					circles = append(circles[:i], circles[i+1:]...)
					break // Stop after removing one
				}
			}
		}

		rl.BeginDrawing()

		rl.ClearBackground(rl.RayWhite)

		rg.SetStyle(rg.DEFAULT, rg.BORDER_COLOR_NORMAL, int64(rl.ColorToInt(rl.Black)))
		rg.SetStyle(rg.BUTTON, rg.TEXT_COLOR_NORMAL, int64(rl.ColorToInt(rl.Black)))

		rg.Button(rl.NewRectangle(50, 50, 40, 40), "Click")
		rg.Button(rl.NewRectangle(100, 50, 40, 40), "Click")
		rg.Button(rl.NewRectangle(150, 50, 40, 40), "Click")
		rg.Button(rl.NewRectangle(200, 50, 40, 40), "Click")

		for _, pos := range circles {
			rl.DrawCircleV(pos, circleRadius, rl.LightGray)
		}

		rl.EndDrawing()
	}
}
