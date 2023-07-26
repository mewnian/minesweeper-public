#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "Global.h"
#include "Board.h"
#include "Button.h"
#include "IdempotentButton.h"
#include "Utilities.h"

class Game 
{
private:
    bool m_disabled{false};
    Board m_board;
    GameState m_gameProgress{GAME_NOT_STARTED};
    Button m_saveButton{Rectangle{568, 36, 144, 48}, Assets::saveButtonTexture};
    Button m_resumeButton{Rectangle{440, 400, 400, 100}, Assets::resumeButtonTexture};
    Button m_mainMenuButton{Rectangle{440, 515, 400, 100}, Assets::mainMenuButtonTexture};
    IdempotentButton m_pauseButton{Rectangle{0, 0, 32, 32}, Assets::pauseButtonTexture};
    std::pair<int, int> m_highlightedCell{-1, -1};
    float m_timer{0.0f};
public:
    Game(int rows = 0, int columns = 0, int bombs = 0);
    Game(const char* filename);
    void disableGame() { m_disabled = true; }
    void enableGame() { m_disabled = false; }
    void SaveToFile();
    WindowState CheckMouseAction(Vector2 currentMousePosition);
    WindowState Update();
    void DrawGameField();
    void Draw();
    bool getGameOutcome() { return m_gameProgress == GAME_OVER_WIN; }
    float getTimeElapsed() { return m_timer; }
    int getRows() { return m_board.getRows(); }
    int getColumns() { return m_board.getColumns(); }
    int getBombs() { return m_board.getBombs(); }
    void ResetGame();
};

#endif