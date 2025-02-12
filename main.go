package main

import (
	"fmt"

	rg "github.com/gen2brain/raylib-go/raygui"
	rl "github.com/gen2brain/raylib-go/raylib"
)

func main() {
	rl.InitWindow(800, 450, "kflap")
	defer rl.CloseWindow()

	rl.SetTargetFPS(60)

	var button bool

	for !rl.WindowShouldClose() {
		rl.BeginDrawing()

		rl.ClearBackground(rl.RayWhite)

		button = rg.Button(rl.NewRectangle(50, 150, 100, 40), "Click")
		if button {
			fmt.Println("Clicked on button")
		}

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
