#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"
#include "laser.h"
#include <vector>
using namespace std;

// 飛船類別的定義
class Spaceship
{
    public:
        Spaceship(); // 飛船的構造函數
        ~Spaceship(); // 飛船的析構函數
        void Draw(); // 繪製飛船
        void MoveLeft(); // 向左移動飛船
        void MoveRight(); // 向右移動飛船
        void Fire(); // 飛船開火
        Rectangle getRect(); // 獲取飛船的矩形邊界
        void Reset(); // 重置飛船位置
        vector<Laser> lasers; // 儲存飛船發射的激光
        int getpositionx(); // 獲取飛船的x軸位置
    private:
        Texture2D image; // 飛船的圖像
        Vector2 position; // 飛船的位置
        double lastFireTime; // 上次開火的時間
        Sound laserSound; // 激光聲音
};

#endif // SPACESHIP_H