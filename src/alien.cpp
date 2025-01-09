#include "alien.h"
#include <iostream>
using namespace std;
std::vector<Texture2D> Alien::alienImages = {};

// 基類建構函數
Alien::Alien(int type, Vector2 position) : type(type), position(position) {
    LoadImages();
}

// 基類解構函數
Alien::~Alien() {
    //UnloadImages();
}

// 載入靜態圖片
void Alien::LoadImages() {
    if (alienImages.empty()) {
        alienImages.push_back(LoadTexture("Graphics/alienwang.png"));
        alienImages.push_back(LoadTexture("Graphics/alienrex.png"));
        alienImages.push_back(LoadTexture("Graphics/alienliao.png"));
    }
}

// 卸載靜態圖片
void Alien::UnloadImages() {
    for (auto& image : alienImages) {
        UnloadTexture(image);
    }
    alienImages.clear();
}

// 繪製基類（預設無行為，子類覆寫）
void Alien::Draw() {}


// 獲取邊框矩形
Rectangle Alien::getRect() {
    return {position.x, position.y, float(alienImages[0].width), float(alienImages[0].height)};
}

// 更新位置
void Alien::Update(int direction) {
    position.x += direction;

    if (position.x < 0) {
        position.x = 0; // 防止超出左邊界
    } else if (position.x + alienImages[0].width > GetScreenWidth()) {
        position.x = GetScreenWidth() - alienImages[0].width; // 防止超出右邊界
    }
}

// Type1 Alien 實作
AlienType1::AlienType1(int type, Vector2 position) : Alien(type,position) {}
void AlienType1::Draw() {
    DrawTextureV(alienImages[0], position, WHITE);
}
int AlienType1::GetType() {
    return 1;
}

// Type2 Alien 實作
AlienType2::AlienType2(int type, Vector2 position) : Alien(type,position) {}
void AlienType2::Draw() {
    DrawTextureV(alienImages[1], position, WHITE);
}
int AlienType2::GetType() {
    return 2;
}

// Type3 Alien 實作
AlienType3::AlienType3(int type, Vector2 position) : Alien(type,position) {}
void AlienType3::Draw() {
    DrawTextureV(alienImages[2], position, WHITE);
}
int AlienType3::GetType() {
    return 3;
}