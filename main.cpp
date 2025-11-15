#include<iostream>
#include "raylib.h"
#include "Logic.cpp"
#include "Chess.hpp"


using namespace std;


int main(){
    InitWindow(boardsize,boardsize,"CHESS");
    SetTargetFPS(30);

    setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        Drawboard(boardsize);
        drawPiecesAndMove();
        EndDrawing();
    }

    for (auto &p : pieces) {   // iterate through the global pieces vector
        p.Unload();            // call the unload function on each piece
    }
    std::cout << "✅ All chess pieces unloaded!" << std::endl;
    CloseWindow();
    return 0;
}