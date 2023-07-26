#include "Utilities.h"

#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{
    m_result = false;
    m_score = 0;
    m_rows = 0;
    m_columns = 0;
    m_bombs = 0;
    m_isPersonalBest = false;
}

GameOverScreen::GameOverScreen(Game& game) 
{
    m_result = game.getGameOutcome();
    m_score = game.getTimeElapsed();
    m_rows = game.getRows();
    m_columns = game.getColumns();
    m_bombs = game.getBombs();
    if (m_result) m_isPersonalBest = PersonalBestScore::UpdateData(m_rows, m_columns, m_bombs, m_score);
    else m_isPersonalBest = false;
}

WindowState GameOverScreen::CheckMouseAction(Vector2 currentMousePosition)
{
    ClickState respond = m_playAgainButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        return GAME_SCREEN;
    }
    respond = m_mainMenuButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        return HOME_SCREEN;
    }
    return GAMEOVER_SCREEN;
}

void GameOverScreen::DrawCenterText(const char* txtContent, float fontSize, float posY, Color color)
{
    Vector2 textSz = MeasureTextEx(Assets::fontSignika, txtContent, fontSize, 1.0);
    Vector2 textPos{(SCREEN_WIDTH - textSz.x) * 0.5f, posY};
    DrawTextEx(Assets::fontSignika, txtContent, textPos, fontSize, 1.0, color);
}

void GameOverScreen::Draw()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BLACK, 0.8));

    if (m_result) DrawCenterText("WIN", 120, 30, GREEN);
    else DrawCenterText("LOSE", 120, 30, RED);
    
    char str[30];
    if (m_isPersonalBest) 
    {
        sprintf(str, "Time spent: %.3f s (NEW PERSONAL BEST!)", m_score);
    }
    else
    {
        sprintf(str, "Time spent: %.3f s", m_score);
    }
    DrawCenterText(str, 40, 165, (m_isPersonalBest ? GOLD : WHITE));
    
    float bestScore = PersonalBestScore::GetPersonalBest(m_rows, m_columns, m_bombs); 
    if (bestScore != INFINITY)
    {
        sprintf(str, "Fastest win on %dx%d board with %d mines: %.3f s", m_rows, m_columns, m_bombs, bestScore);
        DrawCenterText(str, 40, 220, (m_isPersonalBest ? GOLD : WHITE));
    }

    m_playAgainButton.Draw();
    m_mainMenuButton.Draw();
}