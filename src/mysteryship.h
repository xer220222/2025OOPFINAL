#ifndef MYSTERYSHIP_H
#define MYSTERYSHIP_H

#include <raylib.h>

class MysteryShip
{
public:
    MysteryShip();
    ~MysteryShip();
    void Spawn();        // 生成
    Rectangle getRect(); // 碰撞檢測
    void Update();       // 更新
    void Draw();         // 繪製
    void Switchmysteryship(int); //因為血量減少變換顏色
    bool alive;

private:
    Vector2 position;
    Texture2D image;
    int speed;
};

#endif
    