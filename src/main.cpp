#include <raylib.h>

#include "finite_automaton/canvas.h"

int main() {
  FiniteAutomatonCanvas fa;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);

  InitWindow(800, 450, "kflap");

  while (!WindowShouldClose()) {
    fa.run();
  }

  CloseWindow();

  return 0;
}
