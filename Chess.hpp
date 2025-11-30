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
    Vector2 prevPosition;
    bool isDragging;     // For movement with mouse
    bool isWhite;     // white or black
    bool isSelected = false;  //for highlighting piece
    bool isAlive = true;     //is alive or not
    bool WhiteTurn = true;
    
    
    public:
    // Constructor
    Piece(string n, Texture2D tex, Vector2 pos , bool isWh);
    
    // Draw the piece
    void Draw(float boxSize);
    
    // Update (for movement)
    void Update(float boxSize);
    
    // Unload texture
    void Unload();
    
    // Getters
    Vector2 GetPosition() const { return position; }
    string GetName() const { return name; }
    bool GetAlive() const { return isAlive; }
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
    float scale = 1.3f;
    float offsetX = (boxSize - texture.width * scale) / 2;
    float offsetY = (boxSize - texture.height * scale) / 2;
    
    
    if (isAlive)
    {
        DrawTextureEx(texture, {position.x + offsetX, position.y + offsetY}, 0.0f, scale, WHITE);
    }
    
    if (isSelected)
    {
        DrawRectangleLinesEx(
            { prevPosition.x, prevPosition.y, boxSize, boxSize },
            5,      // thickness of the border (increase for more bold)
            GOLD    // color of the border
            );
    }
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

    // Detect if user clicked this piece
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();

        // Check if mouse clicked inside the piece rectangle
        Rectangle rect = { position.x, position.y, (float)texture.width, (float)texture.height };

        if (CheckCollisionPointRec(mouse, rect))
        {
            isSelected = true;      // highlight ON
            isDragging = true;      // start dragging
            prevPosition = position;
        }
        else
        {
            isSelected = false;     // clicked somewhere else → remove highlight
            isDragging = false;
        }
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
        float snappedX = roundf(position.x / boxSize) * boxSize;
        float snappedY = roundf(position.y / boxSize) * boxSize;

        bool blocked = false;

        for (auto &p : pieces)
        {
            // 🚨 IMPORTANT: skip checking yourself
            if (&p == this) continue;

            // If someone is on that square
            if (p.position.x == snappedX && p.position.y == snappedY)
            {
                if (p.isWhite == isWhite)
                {
                    // Same color → ❌ blocked
                    blocked = true;
                }
                else
                {
                    // Opposite color → ✔ capture
                    p.isAlive = false;
                }
            }
        }

    if (blocked)
    {
        // Return to previous square
        position = prevPosition;
    }
    else
    {
        // Valid move → snap into place
        position.x = snappedX;
        position.y = snappedY;
    }

    isDragging = false;
}
}

void Piece::Unload()
{
    UnloadTexture(texture);
}
