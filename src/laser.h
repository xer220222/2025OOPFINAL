#ifndef LASER_H
#define LASER_H

#include "raylib.h"

// 激光類別的定義
class Laser
{
    public:
        Laser(Vector2 position, int speed); // 激光的構造函數，初始化位置和速度
        void Update(); // 更新激光的位置
        void Draw(); // 繪製激光
        Rectangle getRect(); // 獲取激光的矩形邊界
        bool active; // 激光是否處於激活狀態
    private:
        Vector2 position; // 激光的位置
        int speed; // 激光的速度
};

#endif // LASER_H