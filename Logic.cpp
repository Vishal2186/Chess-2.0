#pragma once
#include "raylib.h"
#include <iostream>
#include <vector>
#include "Chess.hpp"


// DS for Peices Creation
std::vector<Piece> pieces;

// Global textures
Texture2D whitePawn, blackPawn;
Texture2D whiteRook, blackRook;
Texture2D whiteKnight, blackKnight;
Texture2D whiteBishop, blackBishop;
Texture2D whiteQueen, blackQueen;
Texture2D whiteKing, blackKing;



// VARIABLES
extern const int boardsize = 800;
extern const float boxsize = static_cast<float>(boardsize) / 8.0f;



//FUNCTIONS
void Drawboard(int size)
{
    int a;
    char l = 65;
    int n = 8;
    for (int i = 0; i < size; i += 100)
    {
        (i%200==0)? a = 0: a = 1;
        for (int j = 0; j < size; j += 100)
        {
            DrawRectangle(j,i,boxsize,boxsize,(a%2==0?DARKGREEN:LIGHTGRAY));
            a++;
            
        }
        DrawText( TextFormat("%d",n) , 10, i + 10, 15, BLACK);
        n--;
    }
    for (int i = 0; i < 800; i+=100)
    {
        DrawText( TextFormat("%c",l) , i + 80, 780, 15, BLACK);
        l++;
    }
        
}

void loadpeices()
{
     whitePawn =  LoadTexture("assets/White_Pawn.png");
     whiteRook =  LoadTexture("assets/White_Rook.png");
     whiteKnight =  LoadTexture("assets/White_Knight.png");
     whiteBishop =  LoadTexture("assets/White_Bishop.png");
     whiteKing =  LoadTexture("assets/White_King.png");
     whiteQueen =  LoadTexture("assets/White_Queen.png");

     blackPawn =  LoadTexture("assets/Black_Pawn.png");
     blackRook =  LoadTexture("assets/Black_Rook.png");
     blackKnight =  LoadTexture("assets/Black_Knight.png");
     blackBishop =  LoadTexture("assets/Black_Bishop.png");
     blackKing =  LoadTexture("assets/Black_King.png");
     blackQueen =  LoadTexture("assets/Black_Queen.png");
    std :: cout << "✅ All chess pieces loaded!\n";
}



void setup()
{
    loadpeices();

    // --- White Pawns ---
    for (int i = 0; i < 8; i++)
        pieces.emplace_back("whitePawn" + std::to_string(i + 1), whitePawn, Vector2{i * boxsize, 6 * boxsize}, true);

    // --- Black Pawns ---
    for (int i = 0; i < 8; i++)
        pieces.emplace_back("blackPawn" + std::to_string(i + 1), blackPawn, Vector2{i * boxsize, 1 * boxsize}, false);

    // --- White Rooks ---
    pieces.emplace_back("whiteRook1", whiteRook, Vector2{0 * boxsize, 7 * boxsize}, true);
    pieces.emplace_back("whiteRook2", whiteRook, Vector2{7 * boxsize, 7 * boxsize}, true);

    // --- Black Rooks ---
    pieces.emplace_back("blackRook1", blackRook, Vector2{0 * boxsize, 0 * boxsize}, false);
    pieces.emplace_back("blackRook2", blackRook, Vector2{7 * boxsize, 0 * boxsize}, false);

    // --- White Knights ---
    pieces.emplace_back("whiteKnight1", whiteKnight, Vector2{1 * boxsize, 7 * boxsize}, true);
    pieces.emplace_back("whiteKnight2", whiteKnight, Vector2{6 * boxsize, 7 * boxsize}, true);

    // --- Black Knights ---
    pieces.emplace_back("blackKnight1", blackKnight, Vector2{1 * boxsize, 0 * boxsize}, false);
    pieces.emplace_back("blackKnight2", blackKnight, Vector2{6 * boxsize, 0 * boxsize}, false);

    // --- White Bishops ---
    pieces.emplace_back("whiteBishop1", whiteBishop, Vector2{2 * boxsize, 7 * boxsize}, true);
    pieces.emplace_back("whiteBishop2", whiteBishop, Vector2{5 * boxsize, 7 * boxsize}, true);

    // --- Black Bishops ---
    pieces.emplace_back("blackBishop1", blackBishop, Vector2{2 * boxsize, 0 * boxsize}, false);
    pieces.emplace_back("blackBishop2", blackBishop, Vector2{5 * boxsize, 0 * boxsize}, false);

    // --- White Queen ---
    pieces.emplace_back("whiteQueen", whiteQueen, Vector2{3 * boxsize, 7 * boxsize}, true);

    // --- Black Queen ---
    pieces.emplace_back("blackQueen", blackQueen, Vector2{3 * boxsize, 0 * boxsize}, false);

    // --- White King ---
    pieces.emplace_back("whiteKing", whiteKing, Vector2{4 * boxsize, 7 * boxsize}, true);

    // --- Black King ---
    pieces.emplace_back("blackKing", blackKing, Vector2{4 * boxsize, 0 * boxsize}, false);

}



void drawPiecesAndMove()
{
    // Draw all piece textures
    for (auto &p : pieces)
{
    p.Draw(boxsize);
    p.Update(boxsize);
}

}