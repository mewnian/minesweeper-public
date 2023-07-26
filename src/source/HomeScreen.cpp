#include "Game.h"

#include "HomeScreen.h"

HomeScreen::HomeScreen() 
{
    if (IsSaveFileValid("../build/savefile.dat")) 
    {
        m_loadButtonVisible = true;
    }
}

WindowState HomeScreen::CheckMouseAction(Vector2 currentMousePosition)
{
    ClickState respond = m_newGameButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        return SELECTION_SCREEN;
    }
    respond = m_loadSavedGameButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        return LOAD_GAME_SCREEN;
    }
    return HOME_SCREEN;
}

void HomeScreen::DrawCenterText(const char* txtContent, float fontSize, float posY)
{
    Vector2 textSz = MeasureTextEx(Assets::fontSignika, txtContent, fontSize, 1.0);
    Vector2 textPos{(SCREEN_WIDTH - textSz.x) * 0.5f, posY};
    DrawTextEx(Assets::fontSignika, txtContent, textPos, fontSize, 1.0, WHITE);
}

void HomeScreen::Draw()
{
    DrawCenterText("MINESWEEPER", 120, 15);
    DrawCenterText("by Bui Nguyen Duc Tan", 30, 120);

    m_newGameButton.Draw();
    if (m_loadButtonVisible) m_loadSavedGameButton.Draw();
}