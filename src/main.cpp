#include"raylib.h"
#include"game.h"
#include <string>

using namespace std;

string FormatWithLeadingZeros(int number, int width) {
    string numberText = to_string(number);
    int leadingZeros = width - numberText.length();
    numberText = string(leadingZeros, '0') + numberText;
    return numberText;
}
int main(){
    int offset =50;
    int windowWidth=750;
    int windowHeight=700;
    InitWindow(windowWidth + offset, windowHeight + 2 * offset,"OOP final project");
    InitAudioDevice();
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D livesImage = LoadTexture("Graphics/lives.png");

    SetTargetFPS(60);
    Game game;
    game.Draw();
    while(WindowShouldClose() == false)
    {   
        cout<<game.spaceship.getpositionx()<<endl;
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, ORANGE);
        DrawLineEx({25, 730}, {775, 730}, 3, ORANGE);
        if(game.running) {
            string Alienlives = "Alien count: " + to_string(game.getalienlives());
            DrawTextEx(font, Alienlives.c_str(), {250, 15}, 34, 2, ORANGE);
            string Enemylives = "Enemy lives: " + to_string(game.getmyteryshiplives());
            DrawTextEx(font, Enemylives.c_str(), {500, 740}, 34, 2, ORANGE);
        } else if(game.getLives() > 0) {
            DrawTextEx(font, "WIN!!!", {650, 740}, 34, 2, ORANGE);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, ORANGE);
        }
        float x = 50.0;
        for(int i = 0; i < game.getLives(); i++) {
            DrawTextureV(livesImage, {x, 745}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15} , 34, 2, ORANGE);
        string scoreText = FormatWithLeadingZeros(game.getScore(), 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, ORANGE);

        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, ORANGE);
        string highscoreText = FormatWithLeadingZeros(game.getHighscore(), 5);
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, ORANGE);

        game.Draw(); 
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
}