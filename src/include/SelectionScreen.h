#ifndef SELECTION_SCREEN_H
#define SELECTION_SCREEN_H

#include "raylib.h"
#include "Global.h"
#include "Button.h"
#include "IdempotentButton.h"

class SelectionScreen 
{
private:
    IdempotentButton m_easyMode{Rectangle{270, 150, 240, 150}, Assets::easyModeTexture};
    IdempotentButton m_mediumMode{Rectangle{520, 150, 240, 150}, Assets::mediumModeTexture};
    IdempotentButton m_hardMode{Rectangle{770, 150, 240, 150}, Assets::hardModeTexture};
    Button m_backButton{Rectangle{440, 600, 150, 50}, Assets::backButtonTexture};
    Button m_playButton{Rectangle{690, 600, 150, 50}, Assets::playButtonTexture};

    Button m_rowsDecraseButton{Rectangle{640, 360, 48, 48}, Assets::decreaseButtonTexture};
    Button m_rowsIncraseButton{Rectangle{962, 360, 48, 48}, Assets::increaseButtonTexture};
    Button m_columnsDecraseButton{Rectangle{640, 420, 48, 48}, Assets::decreaseButtonTexture};
    Button m_columnsIncraseButton{Rectangle{962, 420, 48, 48}, Assets::increaseButtonTexture};
    Button m_bombsDecraseButton{Rectangle{640, 480, 48, 48}, Assets::decreaseButtonTexture};
    Button m_bombsIncraseButton{Rectangle{962, 480, 48, 48}, Assets::increaseButtonTexture};
public:
    SelectionScreen() {}
    void UpdateConfig(int deltaRows, int deltaCols, int deltaBombs);
    WindowState CheckMouseAction(Vector2 currentMousePosition);
    void DrawCenterText(const char* txtContent, float fontSize, float posX, float posY, float width);
    void Draw();
};

#endif