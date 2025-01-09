#include"game.h"

Game::Game()
{   
    explosionSound = LoadSound("Sounds/explosion.ogg");
    InitGame();
}
Game::~Game()
{
    Alien::UnloadImages();
    UnloadSound(explosionSound);
}

void Game :: changescore(int livesleft)
{
    if(livesleft == 3)
    {
        score += 3000;
    }
    else if(livesleft == 2)
    {
        score += 2000;
    }
    else if(livesleft == 1)
    {
        score += 1000;
    }
}

int Game::getmyteryshiplives()
{
    return mysteryshiplive;
}

int Game::getalienlives()
{
    return aliens.size();
}

void Game::Update(){
    if(running){
        double currentTime = GetTime();
        if(aliens.size()<23) //當外星人少於一半
        {
            if(currentTime -timeSinceLastMysteryShip>mysteryShipSpawnInterval){
                mysteryship.Spawn();
                timeSinceLastMysteryShip = currentTime;
                mysteryShipSpawnInterval = GetRandomValue(10, 20);
            }
        }
        for(auto& laser : spaceship.lasers){
            laser.Update();
        }
        moveAliens();
        AlienShootLaser();
        for(auto& laser : alienLasers){
            laser.Update();
        }
        DeleteInactiveLasers();
        mysteryship.Update();
        CheckCollisions();
    }
    else{
        if(IsKeyDown(KEY_ENTER)){
            Reset();
            InitGame();
        }
    }

}

void Game::Draw()
{
    spaceship.Draw();
    for(auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }
    
    for(auto& obstacle: obstacles) {
        obstacle.Draw();
    }

    for(auto& alien: aliens) {
        alien->Draw();
    }

    for(auto& laser: alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw();
}

void Game::HandleInput()
{
    if(running){
        if(IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } 
        else if (IsKeyDown(KEY_RIGHT)){
            spaceship.MoveRight();
        } 
        else if (IsKeyDown(KEY_SPACE)) {
            spaceship.Fire();
        }
    }
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeSinceLastAlienLaser = 0.0;
    timeSinceLastMysteryShip = 0.0;
    lives = 3;
    mysteryshiplive = 3;
    mysteryship.Switchmysteryship(mysteryshiplive);
    mysteryship.alive=false;
    score = 0;
    highscore = loadhighscore();
    running = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
}
int Game::getScore()
{
    return score;
}

int Game::getLives()
{
    return lives;
}

int Game::getHighscore()
{
    return highscore;
}

int Game::loadhighscore()
{
    ifstream file("highscore.txt");
    if(file.is_open())
    {
        int highscore;
        file >> highscore;
        file.close();
        return highscore;
    }
    return 0;
}

void Game::checkhighscore()
{
    if(score > highscore)
    {
        highscore = score;
        savehighscore(highscore);
    }
}

void Game::savehighscore(int highscore)
{
    ofstream file("highscore.txt");
    if(file.is_open())
    {
        file << highscore;
        file.close();
    }
    else
    {
        cout << "Error saving highscore" << endl;
    }
}

void Game::GameOver()
{
    if(lives>0)
    {
        score += lives*1000;
    }
    checkhighscore();
    running = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if(!it -> active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++ it;
        }
    }
    for(auto it = alienLasers.begin(); it != alienLasers.end();){
        if(!it -> active) {
            it = alienLasers.erase(it);
        } else {
            ++ it;
        }
    }
}

void Game::CheckCollisions()
{
    for(auto& laser: spaceship.lasers) {
        auto it = aliens.begin();
        while(it != aliens.end()){
            if(CheckCollisionRecs(it->get()->getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                if(it->get()->GetType() == 1) {
                    score += 100;
                } else if (it->get()->GetType() == 2) {
                    score += 200;
                } else if(it->get()->GetType() == 3) {
                    score += 300;
                }
                checkhighscore();

                it = aliens.erase(it);
                laser.active = false;
                cout<<"Aliens number: "<<aliens.size()<<endl; //目前場上外星人的數量
            } else {
                ++it;
            }
        }

        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            checkhighscore();
            mysteryshiplive--; //神秘船生命減少
            PlaySound(explosionSound);
            if (mysteryshiplive == 0)
            {
                GameOver();
            }
            else
            {
                mysteryship.Switchmysteryship(mysteryshiplive);
            }
        }
    }

    //Alien Lasers

    for(auto& laser: alienLasers) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())){
            laser.active = false;
            lives --;
            if(lives == 0) {
                GameOver();
            }
        }

        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }

    //Alien Collision with Obstacle
    
    for(auto& alien: aliens) {
        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()) {
                if(CheckCollisionRecs(it -> getRect(), alien->getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it ++;
                }
            }
        }

        if(CheckCollisionRecs(alien->getRect(), spaceship.getRect())) {
            lives=0;
            GameOver();
        }
    }
}

vector<Obstacle> Game::CreateObstacles()
{
   int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }
    return obstacles;
}

vector<unique_ptr<Alien>> Game::CreateAliens() {
    vector<unique_ptr<Alien>> aliens;
    for(int row = 0; row < 5; row++) {
        for(int column = 0; column < 11; column++) {

            int alienType;
            if(row == 0) {
                alienType = 3;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = 75 + column * 55;
            float y = 110 + row * 55;

            if (alienType == 1) {
                aliens.push_back(make_unique<AlienType1>(alienType, Vector2{x, y}));
            } else if (alienType == 2) {
                aliens.push_back(make_unique<AlienType2>(alienType, Vector2{x, y}));
            } else if (alienType == 3) {
                aliens.push_back(make_unique<AlienType3>(alienType, Vector2{x, y}));
            }
        }
    }
    return aliens;
}

void Game::moveAliens()
{
    for(auto& alien: aliens) {
        if(alien->position.x + alien->alienImages[alien->GetType() - 1].width > GetScreenWidth() - 25 ) {
            moveAliensDown(4);
            aliensDirection = -1;
        }
        if(alien->position.x < 25) {
            moveAliensDown(4);
            aliensDirection = 1;
        }

        alien->Update(aliensDirection);
    }
}

void Game::moveAliensDown(int distance)
{
    for(auto& alien: aliens) {
        alien->position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if(currentTime - timeSinceLastAlienLaser >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = *aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.GetType() -1].width/2, 
                                    alien.position.y + alien.alienImages[alien.GetType() - 1].height}, 6));
        timeSinceLastAlienLaser = GetTime();
    }
}