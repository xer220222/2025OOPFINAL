#ifndef ALIEN_H
#define ALIEN_H

#include "raylib.h"
#include <vector>

class Alien {
protected:
    int type;
public:
    Alien(int type, Vector2 position);
    virtual ~Alien();
    virtual void Draw()=0;            // 繪製外星人
    virtual Rectangle getRect();    // 獲取邊框矩形
    virtual int GetType()=0;
    static std::vector<Texture2D> alienImages; // 靜態圖片資源
    static void LoadImages();       // 載入靜態圖片
    static void UnloadImages();     // 卸載靜態圖片
    Vector2 position;   // 位置
    void Update(int direction);     // 更新位置
};

class AlienType1 : public Alien {
public:
    AlienType1(int type, Vector2 position);
    void Draw() override;
    int GetType() override;
};

class AlienType2 : public Alien {
public:
    AlienType2(int type, Vector2 position);
    void Draw() override;
    int GetType() override;
};

class AlienType3 : public Alien {
public:
    AlienType3(int type, Vector2 position);
    void Draw() override;
    int GetType() override;
};

#endif // ALIEN_H
