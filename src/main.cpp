#include <iostream>
#include <pugixml.hpp>
#include <raylib.h>

#include "finite_automaton/canvas.h"

int main()
{
    // begin experiment
    pugi::xml_document doc;

    if (!doc.load_file("examples/DFA.jff")) {
        std::cerr << "Failed to load XML file.\n";
        return 1;
    }

    pugi::xml_node type = doc.child("structure").child("type");
    std::cout << type.text().as_string() << "\n";
    // end experiment

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
