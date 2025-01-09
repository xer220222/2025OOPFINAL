#include "laser.h"
#include <iostream>

// 激光的基礎設置
Laser::Laser(Vector2 position, int speed)
{
    this->position = position; // 設置激光的位置
    this->speed = speed; // 設置激光的速度
    active = true; // 激光初始為激活狀態
}

// 繪製激光
void Laser::Draw()
{
    if(active) // 如果激光處於激活狀態
    {
        DrawRectangle(position.x, position.y, 4, 15, (Color){243, 216, 63, 255}); // 繪製激光
    }
}

// 獲取激光的矩形邊界
Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x; // 設置矩形的x軸位置
    rect.y = position.y; // 設置矩形的y軸位置
    rect.width = 4; // 設置矩形的寬度
    rect.height = 15; // 設置矩形的高度
    return rect; // 返回矩形
}

// 更新激光的位置
void Laser::Update()
{
    position.y += speed; // 根據速度更新激光的y軸位置
    if(active) // 如果激光處於激活狀態
    {
        if(position.y > GetScreenHeight() - 100 || position.y < 25) // 如果激光超出屏幕邊界
        {
            active = false; // 將激光設置為非激活狀態
        }
    }
}
