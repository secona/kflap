package main

import (
	"fmt"

	rg "github.com/gen2brain/raylib-go/raygui"
	rl "github.com/gen2brain/raylib-go/raylib"
)

func main() {
	rl.SetConfigFlags(rl.FlagWindowResizable)
	rl.SetTargetFPS(60)

	rl.InitWindow(800, 450, "kflap")
	defer rl.CloseWindow()

	for !rl.WindowShouldClose() {
		rl.BeginDrawing()

		rl.ClearBackground(rl.RayWhite)

		rg.SetStyle(rg.DEFAULT, rg.BORDER_COLOR_NORMAL, int64(rl.ColorToInt(rl.Black)))
		rg.SetStyle(rg.BUTTON, rg.TEXT_COLOR_NORMAL, int64(rl.ColorToInt(rl.Black)))

		rg.Button(rl.NewRectangle(50, 50, 40, 40), "Click")
		rg.Button(rl.NewRectangle(100, 50, 40, 40), "Click")
		rg.Button(rl.NewRectangle(150, 50, 40, 40), "Click")
		rg.Button(rl.NewRectangle(200, 50, 40, 40), "Click")

		if (rl.IsKeyPressed(rl.KeyOne)) {
			fmt.Println("1")
		}

		if (rl.IsKeyPressed(rl.KeyTwo)) {
			fmt.Println("2")
		}

		if (rl.IsKeyPressed(rl.KeyThree)) {
			fmt.Println("3")
		}

		rl.EndDrawing()
	}
}
