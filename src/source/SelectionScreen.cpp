#include <algorithm>
#include <cstdio>

#include "SelectionScreen.h"

void SelectionScreen::UpdateConfig(int deltaRows, int deltaCols, int deltaBombs)
{
    N_ROWS = std::min(std::max(MIN_ROWS, N_ROWS + deltaRows), MAX_ROWS);
    N_COLS = std::min(std::max(MIN_COLS, N_COLS + deltaCols), MAX_COLS);
    N_BOMBS = std::min(std::max(MIN_BOMBS, N_BOMBS + deltaBombs), N_ROWS * N_COLS - 1);
}

WindowState SelectionScreen::CheckMouseAction(Vector2 currentMousePosition)
{
    m_easyMode.SetFalse();
    m_mediumMode.SetFalse();
    m_hardMode.SetFalse();
    ClickState respond = m_easyMode.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        N_ROWS = 9, N_COLS = 9, N_BOMBS = 10;
    }
    respond = m_mediumMode.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        N_ROWS = 16, N_COLS = 16, N_BOMBS = 40;
    }
    respond = m_hardMode.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        N_ROWS = 16, N_COLS = 30, N_BOMBS = 99;
    }

    if (N_ROWS == 9 && N_COLS == 9 && N_BOMBS == 10) m_easyMode.SetTrue();
    if (N_ROWS == 16 && N_COLS == 16 && N_BOMBS == 40) m_mediumMode.SetTrue();
    if (N_ROWS == 16 && N_COLS == 30 && N_BOMBS == 99) m_hardMode.SetTrue();

    respond = m_rowsDecraseButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) UpdateConfig(-1, 0, 0);
    respond = m_rowsIncraseButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) UpdateConfig(1, 0, 0);
    respond = m_columnsDecraseButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) UpdateConfig(0, -1, 0);
    respond = m_columnsIncraseButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) UpdateConfig(0, 1, 0);
    respond = m_bombsDecraseButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) UpdateConfig(0, 0, -1);
    respond = m_bombsIncraseButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) UpdateConfig(0, 0, 1);

    respond = m_backButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        return HOME_SCREEN;
    }
    respond = m_playButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        return GAME_SCREEN;
    }
    return SELECTION_SCREEN;
}

void SelectionScreen::DrawCenterText(const char* txtContent, float fontSize, float posX, float posY, float width)
{
    Vector2 textSz = MeasureTextEx(Assets::fontSignika, txtContent, fontSize, 1.0);
    Vector2 textPos{posX + (width - textSz.x) * 0.5f, posY};
    DrawTextEx(Assets::fontSignika, txtContent, textPos, fontSize, 1.0, WHITE);
}

void SelectionScreen::Draw()
{
    DrawCenterText("CHOOSE MODE", 120, 0, 15, SCREEN_WIDTH);

    m_easyMode.Draw();
    m_mediumMode.Draw();
    m_hardMode.Draw();

    char str[10];

    sprintf(str, "%d", N_ROWS);
    DrawCenterText(str, 48, 688, 360, 274);
    DrawTextEx(Assets::fontSignika, "Rows (3 - 24) ", Vector2{270, 360}, 48, 1.0, WHITE);
    if (N_ROWS > MIN_ROWS) m_rowsDecraseButton.Draw();
    if (N_ROWS < MAX_ROWS) m_rowsIncraseButton.Draw();

    sprintf(str, "%d", N_COLS);
    DrawCenterText(str, 48, 688, 420, 274);
    DrawTextEx(Assets::fontSignika, "Columns (3 - 30)", Vector2{270, 420}, 48, 1.0, WHITE);
    if (N_COLS > MIN_COLS) m_columnsDecraseButton.Draw();
    if (N_COLS < MAX_COLS) m_columnsIncraseButton.Draw();

    sprintf(str, "%d", N_BOMBS);
    DrawCenterText(str, 48, 688, 480, 274);
    DrawTextEx(Assets::fontSignika, "Mines", Vector2{270, 480}, 48, 1.0, WHITE);
    if (N_BOMBS > MIN_BOMBS) m_bombsDecraseButton.Draw();
    if (N_BOMBS < N_ROWS * N_COLS - 1) m_bombsIncraseButton.Draw();
    
    m_backButton.Draw();
    m_playButton.Draw();
}