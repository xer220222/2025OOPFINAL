#pragma once
#include <raylib.h>

class Block {
    public:
        Block(Vector2 position);
        void Draw(Color blockColor);
        Rectangle getRect();

        Vector2 position;
};