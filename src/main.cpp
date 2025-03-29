#include <raylib.h>

#include "finite_automaton/renderer.h"

int main() {
  FiniteAutomatonRenderer fa;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);

  InitWindow(800, 450, "kflap");

  while (!WindowShouldClose()) {
    fa.run();
  }

  CloseWindow();

  return 0;
}
