#include "block.h"

Block::Block(Vector2 position)
{
    this -> position = position;
}

void Block::Draw(Color blockColor) {
    //陰影
    DrawRectangle(position.x + 6, position.y + 6, 3, 3, DARKGRAY);
    // 背景顏色
    DrawRectangle(position.x, position.y, 3, 3, blockColor);
    // 邊框顏色
    //DrawRectangleLines(position.x, position.y, 3, 3, YELLOW);  // 這裡可以改成其他顏色
}
Rectangle Block::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}