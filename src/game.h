#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mysteryship.h"
using namespace std;

class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        Music music;
        bool running;
        int getScore();
        int getLives();
        int getHighscore();
        void changescore(int livesleft);
        int getmyteryshiplives();
        Spaceship spaceship;
        int getalienlives();
    private:
        void InitGame();
        int score;
        int lives;
        int mysteryshiplive;
        int highscore;
        int loadhighscore();
        void checkhighscore();
        void savehighscore(int highscore);
        void GameOver();
        void Reset();
        //Spaceship spaceship;
        void DeleteInactiveLasers();
        void CheckCollisions();
        vector<Obstacle> obstacles;
        vector<Obstacle> CreateObstacles();
        vector<unique_ptr<Alien>> aliens;  // 修改為智能指針
        vector<unique_ptr<Alien>> CreateAliens();
        int aliensDirection;
        void moveAliens();
        void moveAliensDown(int distance);
        void AlienShootLaser();
        vector<Laser> alienLasers;
        constexpr static float alienLaserShootInterval = 0.35;
        float timeSinceLastAlienLaser;
        MysteryShip mysteryship;
        float timeSinceLastMysteryShip;
        float mysteryShipSpawnInterval;
        Sound explosionSound;
};