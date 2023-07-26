#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include "raylib.h"

#include "Global.h"
#include "Button.h"

class HomeScreen 
{
private:
    Button m_newGameButton{Rectangle{390, 245, 500, 100}, Assets::newGameButtonTexture};
    bool m_loadButtonVisible;
    Button m_loadSavedGameButton{Rectangle{390, 360, 500, 100}, Assets::loadSavedGameButtonTexture};
public:
    HomeScreen();
    WindowState CheckMouseAction(Vector2 currentMousePosition);
    void DrawCenterText(const char* txtContent, float fontSize, float posY);
    void Draw();
};

#endif