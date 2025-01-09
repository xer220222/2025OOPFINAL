#include "mysteryship.h"

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery1.png");
    alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

// 從左側或右側隨機生成飛船 根據生成方向設置速度值（正數向右，負數向左）
void MysteryShip::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if (side == 0)
    {
        position.x = 25;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;
}

// 回傳一個矩形範圍 進行碰撞檢測
Rectangle MysteryShip::getRect()
{
    if (alive)
    {
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else
    {
        return {0, 0, 0, 0};
    }
}

// 控制飛船的位置更新 使其左右移動 如果飛船移動超出指定範圍 設為「不存活」狀態
void MysteryShip::Update()
{
    if (alive)
    {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25)
        {
            alive = false;
        }
    }
}

// 只有當飛船處於「存活」狀態 才會進行繪製
void MysteryShip::Draw()
{
    if (alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}

void MysteryShip::Switchmysteryship(int live)
{
    UnloadTexture(image);
    switch (live)
    {
    case 1:
        image = LoadTexture("Graphics/mystery3.png");
        break;

    case 2:
        image = LoadTexture("Graphics/mystery2.png");
        break;
    
    case 3:
        image = LoadTexture("Graphics/mystery1.png");
        break;

    default:
        image = LoadTexture("Graphics/mystery1.png");
        break;
    }
}
