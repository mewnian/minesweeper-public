#include <fstream>
#include <iomanip>
#include <vector>

#include "Game.h"

Game::Game(int rows, int columns, int bombs)
{
    if (rows && columns && bombs)
    {
        m_board = Board(rows, columns, bombs);
    }
}

Game::Game(const char* filename)
{
    if (IsSaveFileValid(filename))
    {
        std::ifstream inf;
        inf.open(filename);
        int b_rows, b_cols, b_bombs, b_opens, b_flags;
        inf >> b_rows >> b_cols >> b_bombs >> b_opens >> b_flags;
        std::vector< std::vector<int> > b_board(b_rows, std::vector<int>(b_cols, 0));
        for (int i = 0; i < b_rows; ++i)
            for (int j = 0; j < b_cols; ++j)
                inf >> b_board[i][j];
        float b_timer;
        inf >> b_timer;
        inf.close();

        m_disabled = false;
        m_board = Board(b_rows, b_cols, b_bombs);
        m_board.LoadBoard(b_opens, b_flags, b_board);
        m_gameProgress = GAME_ONGOING;
        m_highlightedCell = {-1, -1};
        m_timer = b_timer;
    }
    else
    {
        DrawText("Loading save file failed. Default mode is loaded instead.", 0, 0, 24, WHITE);
        m_board = Board(N_ROWS, N_COLS, N_BOMBS);
    }
}

void Game::SaveToFile()
{
    std::ofstream ouf;
    char filename[100];
    sprintf(filename, "../build/savefile.dat");
    ouf.open(filename);
    if (!ouf)
    {
        throw "Could not open file";
    }
    int b_rows, b_cols, b_bombs, b_opens, b_flags;
    std::tie(b_rows, b_cols, b_bombs, b_opens, b_flags) = m_board.getSaveConfig();
    ouf << b_rows << " " << b_cols << " " << b_bombs << " " << b_opens << " " << b_flags << std::endl;
    for (int i = 0; i < b_rows; ++i)
        for (int j = 0; j < b_cols; ++j)
        {
            ouf << m_board.getCellSaveState(i, j);
            if (j != b_cols - 1) ouf << " ";
            else ouf << std::endl;
        }
    ouf << std::fixed << std::setprecision(6) << m_timer;
    ouf.close();
}

WindowState Game::CheckMouseAction(Vector2 currentMousePosition)
{
    if (!m_disabled)
    {
        if (m_gameProgress != GAME_OVER_LOSE && m_gameProgress != GAME_OVER_WIN)
        {
            m_board.CheckAction(currentMousePosition, m_highlightedCell);
            ClickState respond = m_saveButton.CheckAction(currentMousePosition);
            if (respond == LEFT_CLICK) SaveToFile();
        }
    }
    else
    {
        ClickState respond = m_resumeButton.CheckAction(currentMousePosition);
        if (respond == LEFT_CLICK) 
        {
            m_pauseButton.ToggleState();
            enableGame();
        }
        respond = m_mainMenuButton.CheckAction(currentMousePosition);
        if (respond == LEFT_CLICK) 
        {
            return HOME_SCREEN;
        }
    }
    ClickState respond = m_pauseButton.CheckAction(currentMousePosition);
    if (respond == LEFT_CLICK) 
    {
        m_pauseButton.ToggleState();
        if (m_pauseButton.GetState()) disableGame();
        else enableGame();
    }
    return GAME_SCREEN;
}

WindowState Game::Update()
{
    if (!m_disabled)
    {
        short newProgress = m_board.IsGameOngoing();
        if ((newProgress == GAME_OVER_LOSE || newProgress == GAME_OVER_WIN) && newProgress != m_gameProgress)
        {
            m_board.GameOver(newProgress);
        }
        m_gameProgress = newProgress;
        if (m_gameProgress == GAME_ONGOING) m_timer += GetFrameTime();
    }
    return ((m_gameProgress == GAME_OVER_WIN || m_gameProgress == GAME_OVER_LOSE) ? GAMEOVER_SCREEN : GAME_SCREEN);
}

void Game::DrawGameField()
{
    m_board.DrawBoard();

    Rectangle infoBox = Rectangle{(SCREEN_WIDTH - 880) * 0.5f, (BOARD_MARGIN_TOP - 60) * 0.5f, 880, 60};
    const float FONT_SIZE = 48, FONT_Y = infoBox.y + (infoBox.height - FONT_SIZE) / 2;
    DrawRectangleRounded(infoBox, 0.5f, 1, ColorAlpha(GRAY, 0.5f));
    if (m_gameProgress == GAME_ONGOING) m_saveButton.Draw();
    char str[30];
    {
        int roundedTime = floor(m_timer);
        int ms = roundedTime / 60, ss = roundedTime % 60;
        sprintf(str, "Time: %d:%02d", ms, ss);
        Color colorTxt = m_gameProgress == GAME_OVER_WIN ? GREEN : (m_gameProgress == GAME_OVER_LOSE ? RED : WHITE);
        DrawTextEx(Assets::fontSignika, str, Vector2{300, FONT_Y}, FONT_SIZE, 1.0, colorTxt);
    }
    sprintf(str, "Flags: %d", m_board.getRemainingFlags());
    DrawTextEx(Assets::fontSignika, str, Vector2{780, FONT_Y}, FONT_SIZE, 1.0, WHITE);
}

void Game::Draw()
{
    DrawGameField();

    if (m_disabled)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BLACK, 0.8));
        Vector2 textSz = MeasureTextEx(Assets::fontSignika, "PAUSED", 120, 1.0);
        Vector2 textPos{(SCREEN_WIDTH - textSz.x) * 0.5f, 145};
        DrawTextEx(Assets::fontSignika, "PAUSED", textPos, 120, 1.0, WHITE);
        m_resumeButton.Draw();
        m_mainMenuButton.Draw();
    }

    if (m_gameProgress == GAME_ONGOING) 
    {
        m_pauseButton.Draw();
    }
}

void Game::ResetGame()
{
    int b_rows, b_cols, b_bombs, b_opens, b_flags;
    std::tie(b_rows, b_cols, b_bombs, b_opens, b_flags) = m_board.getSaveConfig();

    m_disabled = false;
    m_board = Board(b_rows, b_cols, b_bombs);
    m_gameProgress = GAME_NOT_STARTED;
    m_highlightedCell = {-1, -1};
    m_timer = 0;
}