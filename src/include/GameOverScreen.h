#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "raylib.h"

#include "Global.h"
#include "Button.h"
#include "Game.h"

class GameOverScreen 
{
private:
    bool m_result;
    float m_score;
    int m_rows, m_columns, m_bombs;
    bool m_isPersonalBest{false};
    Button m_playAgainButton{Rectangle{440, 400, 400, 100}, Assets::playAgainButtonTexture};
    Button m_mainMenuButton{Rectangle{440, 515, 400, 100}, Assets::mainMenuButtonTexture};
public:
    GameOverScreen();
    GameOverScreen(Game& game);
    WindowState CheckMouseAction(Vector2 currentMousePosition);
    void DrawCenterText(const char* txtContent, float fontSize, float posY, Color color);
    void Draw();
};

#endif