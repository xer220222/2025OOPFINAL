#include "spaceship.h"

// 飛船的基礎設置
Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship5.png"); // 加載飛船圖像
    laserSound = LoadSound("Sounds/mylaser.ogg"); // 加載激光聲音
    position.x = (GetScreenWidth() - image.width)/2; // 設置飛船的初始x軸位置
    position.y = GetScreenHeight() - image.height - 100; // 設置飛船的初始y軸位置
    lastFireTime = 0.0; // 會在fire()中記錄每次開火的時間
}

// 釋放資源
Spaceship::~Spaceship()
{
    UnloadTexture(image); // 卸載飛船圖像
    UnloadSound(laserSound); // 卸載激光聲音
}

int Spaceship::getpositionx()
{
    return position.x;
}
// 繪製飛船
void Spaceship::Draw()
{
    DrawTextureV(image,position,WHITE); // 繪製飛船圖像
}

// 向左移動飛船
void Spaceship::MoveLeft()
{
    position.x-=7; // 每次向左移動7個單位
    if(position.x<25) // 確保飛船不會移出左邊界
    {
        position.x=25; // 設置飛船的最左位置
    }
}

// 向右移動飛船
void Spaceship::MoveRight()
{
    position.x+=7; // 每次向右移動7個單位
    if(position.x>GetScreenWidth()-image.width-25) // 確保飛船不會移出右邊界
    {
        position.x=GetScreenWidth()-image.width-25; // 設置飛船的最右位置
    }
}

// 飛船開火
void Spaceship::Fire()
{
    if(GetTime() - lastFireTime >= 0.35) // 控制開火間隔為0.35秒 (可自定義)
    {
        lasers.push_back(Laser({position.x+image.width/2 - 2,position.y},-6)); // 發射激光
        lastFireTime = GetTime(); // 記錄上次開火時間
        PlaySound(laserSound); //開火聲音 
    }
}

// 獲取飛船的矩形邊界
Rectangle Spaceship::getRect()
{
    return{position.x,position.y,float(image.width),float(image.height)}; // 返回飛船的矩形邊界
}

// 重置飛船位置
void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2.0f; // 重置飛船的x軸位置
    position.y = GetScreenHeight() - image.height - 100; // 重置飛船的y軸位置
    lasers.clear(); // 清空激光列表
}