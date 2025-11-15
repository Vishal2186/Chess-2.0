#pragma once

#include "raylib.h"
#include <string>
#include <iostream>
using namespace std;



//CLASSES
class Piece
{
    private:
    string name;         // "Pawn", "Rook", etc.
    Texture2D texture;   // Image of the piece
    Vector2 position;    // Actual position on screen
    bool isDragging;     // For movement with mouse
    bool isWhite;     // white or black
    
    
    public:
    // Constructor
    Piece(string n, Texture2D tex, Vector2 pos , bool isWhite);
    
    // Draw the piece
    void Draw(float boxSize);
    
    // Update (for movement)
    void Update(float boxSize);
    
    // Unload texture
    void Unload();
    
    // Getters
    Vector2 GetPosition() const { return position; }
    string GetName() const { return name; }
};


// DS for Pieces Creation
extern std::vector<Piece> pieces;




Piece::Piece(string n, Texture2D tex, Vector2 pos, bool isWh)
{
    name = n;
    texture = tex;
    position = pos;
    isDragging = false;
    isWhite = isWh;
}

void Piece::Draw(float boxSize)
{
    float scale = 1.0f;
    float offsetX = (boxSize - texture.width * scale) / 2;
    float offsetY = (boxSize - texture.height * scale) / 2;
    
    DrawTextureEx(texture, {position.x + offsetX, position.y + offsetY}, 0.0f, scale, WHITE);
}

void Piece::Update(float boxSize = 100)
{
    Vector2 mouse = GetMousePosition();

    Rectangle pieceRect = {
        position.x,
        position.y,
        boxSize,
        boxSize
    };

    // If mouse clicks the piece
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, pieceRect))
    {
        isDragging = true;
    }

    // Move piece with mouse
    if (isDragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        position.x = mouse.x - boxSize / 2;
        position.y = mouse.y - boxSize / 2;
    }

    // Drop it when mouse is released
    if (isDragging && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        cout<<"peice position before "<<position.x<<" and "<<position.y<<endl;
        position.x = roundf(position.x / boxSize) * boxSize;
        position.y = roundf(position.y / boxSize) * boxSize;
        isDragging = false;
        cout<<"peice position after "<<position.x<<" and "<<position.y<<endl;
    }
}

void Piece::Unload()
{
    UnloadTexture(texture);
}
