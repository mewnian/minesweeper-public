#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>

#include "raylib.h"

#include "Global.h"
#include "BoardCell.h"

class Board
{
private:
    bool m_disabled;
    int m_rows;
    int m_columns;
    int m_bombs;
    int m_cellsOpened;
    int m_cellsFlagged;
    bool m_bombsOpened;
    std::vector< std::vector<BoardCell> > m_board;
public:
    Board(int rows = 0, int columns = 0, int bombs = 0);
    Board& operator=(const Board& board);
    void disableBoard();
    void enableBoard();
    bool isValidCell(int x, int y);
    std::vector< std::pair<int, int> > getNeighboringCells(int x, int y);
    void RevealCells(int x, int y);
    void SetBombNeighbors();
    void GenerateBombs(int bombs, std::pair<int, int> sourceCell = {-1, -1});
    void DrawBoard();
    void CheckAction(Vector2& currentMousePosition, std::pair<int, int>& m_highlightedCell);
    short IsGameOngoing();
    void GameOver(GameState outcome);
    int getRows() { return m_rows; }
    int getColumns() { return m_columns; }
    int getBombs() { return m_bombs; }
    int getRemainingFlags() { return m_bombs - m_cellsFlagged; }
    SaveConfig getSaveConfig() { return {m_rows, m_columns, m_bombs, m_cellsOpened, m_cellsFlagged}; }
    int getCellSaveState(int x, int y);
    void SetState(int x, int y, int state);
    void LoadBoard(int opens, int flags, std::vector< std::vector<int> > board);
};

#endif