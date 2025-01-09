#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "block.h"

class Obstacle {
private:
    Vector2 position;
    Color blockColor;  // 整個障礙物的顏色

public:
    Obstacle(Vector2 position);
    void Draw();
    void RandomizeColor();  // 隨機生成障礙物顏色
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;
};

#endif // OBSTACLE_H
