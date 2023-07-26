#include <cassert>
#include <cmath>

#include "Utilities.h"

#include "Board.h"

Board::Board(int rows, int columns, int bombs)
{
    m_disabled = false;
    m_rows = rows;
    m_columns = columns;
    m_bombs = bombs;
    m_cellsOpened = 0;
    m_cellsFlagged = 0;
    m_bombsOpened = false;
    // m_highlightedCell = {-1, -1};
    m_board.clear();
    m_board.assign(m_rows, std::vector<BoardCell>(m_columns, BoardCell()));
    // board canvas = 1200w x 560h
    // max size of cell = 100px
    if (rows && columns)
    {
        float cellSize = floor(std::min({100.0f, BOARD_CANVAS_WIDTH / columns, BOARD_CANVAS_HEIGHT / rows}));
        float boardsizeX = columns * cellSize, boardsizeY = rows * cellSize;
        float centerX = BOARD_MARGIN_LEFT + BOARD_CANVAS_WIDTH * 0.5f, 
                centerY = BOARD_MARGIN_TOP + BOARD_CANVAS_HEIGHT * 0.5f;
        float topLeftX = centerX - boardsizeX * 0.5f,
                topLeftY = centerY - boardsizeY * 0.5f;
        for (int i = 0; i < m_rows; ++i)
            for (int j = 0; j < m_columns; ++j)
            {
                float cellPosX = topLeftX + j * cellSize, cellPosY = topLeftY + i * cellSize;
                m_board[i][j] = BoardCell(Rectangle{cellPosX, cellPosY, cellSize, cellSize});
            }
    }
}

Board& Board::operator=(const Board& board)
{
    m_disabled = board.m_disabled;
    m_rows = board.m_rows;
    m_columns = board.m_columns;
    m_bombs = board.m_bombs;
    m_cellsOpened = board.m_cellsOpened;
    m_cellsFlagged = board.m_cellsFlagged;
    m_bombsOpened = board.m_bombsOpened;
    // m_highlightedCell = board.m_highlightedCell;
    m_board.clear();
    m_board.insert(m_board.end(), board.m_board.begin(), board.m_board.end());
    return *this;
}

void Board::disableBoard()
{
    m_disabled = true;
}

void Board::enableBoard()
{
    m_disabled = false;
}

bool Board::isValidCell(int x, int y)
{
    return (x >= 0 && y >= 0 && x < m_rows && y < m_columns);
}

std::vector< std::pair<int, int> > Board::getNeighboringCells(int x, int y)
{
    std::vector< std::pair<int, int> > cells;
    const int dx[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    const int dy[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    for (int i = 0; i < 8; ++i)
    {
        int tx = x + dx[i], ty = y + dy[i];
        if (isValidCell(tx, ty)) cells.push_back(std::make_pair(tx, ty));
    }
    return cells;
}

void Board::RevealCells(int x, int y)
{
    ++m_cellsOpened;
    m_board[x][y].setOpened();
    if (m_board[x][y].isBomb())
    {
        m_bombsOpened = true;
        return;
    }
    else
    {
        if (m_board[x][y].getBombNeighbors() == 0)
        {
            for (auto& t : getNeighboringCells(x, y))
            {
                int tx, ty; std::tie(tx, ty) = t;
                if (!m_board[tx][ty].isBomb() && !m_board[tx][ty].isFlagged() && !m_board[tx][ty].isOpened()) RevealCells(tx, ty);
            }
        }
    }
}

void Board::SetBombNeighbors()
{
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < m_columns; ++j)
        {
            int cntBombs = 0;
            for (auto& t : getNeighboringCells(i, j)) 
            {
                int tx, ty; std::tie(tx, ty) = t;
                cntBombs += m_board[tx][ty].isBomb();
            }
            m_board[i][j].setBombNeighbors(cntBombs);
        }
}

void Board::GenerateBombs(int bombs, std::pair<int, int> sourceCell)
{
    int sourceX, sourceY; std::tie(sourceX, sourceY) = sourceCell;
    {
        assert((sourceX == -1 || sourceY == -1 || (sourceX >= 0 && sourceX < m_rows && sourceY >= 0 && sourceY < m_columns)));
    }
    std::vector< std::pair<int, int> > normalCells, neighborCells;
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < m_columns; ++j)
        {
            int distance = std::max(std::abs(i - sourceX), std::abs(j - sourceY));
            if (distance == 1) neighborCells.push_back(std::make_pair(i, j));
            else if (distance >= 2) normalCells.push_back(std::make_pair(i, j));
        }
    Random::shuffleList(normalCells);
    Random::shuffleList(neighborCells);
    int bombed = 0;
    for (auto& cell : normalCells)
    {
        if (bombed >= bombs) break;
        int x, y; std::tie(x, y) = cell;
        m_board[x][y].setBomb();
        ++bombed;
    }
    for (auto& cell : neighborCells)
    {
        if (bombed >= bombs) break;
        int x, y; std::tie(x, y) = cell;
        m_board[x][y].setBomb();
        ++bombed;
    }
    if (bombed < bombs)
    {
        m_board[sourceX][sourceY].setBomb();
        ++bombed;
    }
    SetBombNeighbors();
}

void Board::DrawBoard()
{
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < m_columns; ++j)
        {
            m_board[i][j].draw();
        }
}

void Board::CheckAction(Vector2& currentMousePosition, std::pair<int, int>& m_highlightedCell)
{
    if (m_disabled) return;
    if (m_highlightedCell.first == -1 || m_highlightedCell.second == -1)
    {
        for (int i = 0; i < m_rows; ++i)
            for (int j = 0; j < m_columns; ++j)
            {
                if (m_board[i][j].isOpened()) continue;
                if (CheckCollisionPointRec(currentMousePosition, m_board[i][j].getRect()))
                {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) 
                    {
                        if (m_board[i][j].holdMouse()) m_highlightedCell = {i, j};
                        break;
                    }
                }
                else 
                {
                    m_board[i][j].setDefault();
                }
            }
    }
    else
    {
        int x, y; 
        std::tie(x, y) = m_highlightedCell;
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            if (CheckCollisionPointRec(currentMousePosition, m_board[x][y].getRect()))
            {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
                {
                    switch (m_board[x][y].leftClick())
                    {
                        case 1:
                            if (m_cellsOpened == 0)
                            {
                                GenerateBombs(m_bombs, std::make_pair(x, y));
                            }
                            RevealCells(x, y);
                            break;
                    }
                }
                else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) 
                {
                    switch (m_board[x][y].rightClick())
                    {
                        case 1:
                            if (m_cellsFlagged < m_bombs)
                            {
                                m_board[x][y].setFlag();
                                ++m_cellsFlagged;
                            }
                            break;
                        case 2:
                            if (m_cellsFlagged > 0)
                            {
                                m_board[x][y].setNormal();
                                --m_cellsFlagged;
                            }
                            break;
                    }
                }
            }
            if (m_board[x][y].isFlagged()) m_board[x][y].setFlag();
            else if (m_board[x][y].isOpened()) m_board[x][y].setOpened();
            else m_board[x][y].setNormal();
            m_highlightedCell = {-1, -1};
        }
        else m_board[x][y].setHighlight();
    }
}

short Board::IsGameOngoing()
{
    if (m_cellsOpened == 0) return GAME_NOT_STARTED;
    if (m_bombsOpened) return GAME_OVER_LOSE;
    int cells = m_rows * m_columns;
    if (m_cellsOpened == cells - m_bombs) return GAME_OVER_WIN;
    return GAME_ONGOING;
}

void Board::GameOver(GameState outcome)
{
    if (outcome == GAME_OVER_WIN)
    {
        for (int i = 0; i < m_rows; ++i)
            for (int j = 0; j < m_columns; ++j)
            {
                if (m_board[i][j].isBomb()) 
                {
                    if (!m_board[i][j].isFlagged()) 
                    {
                        ++m_cellsFlagged;
                        m_board[i][j].setFlag();
                    }
                }
            }
    }
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < m_columns; ++j)
        {
            m_board[i][j].setRevealed();
        }
    disableBoard();
}

int Board::getCellSaveState(int x, int y)
{
    if (m_board[x][y].isBomb() && m_board[x][y].isFlagged()) return -2;
    if (m_board[x][y].isBomb()) return -1;
    if (m_board[x][y].isOpened()) return 1;
    if (m_board[x][y].isFlagged()) return 2;
    return 0;
}

void Board::SetState(int x, int y, int state)
{
    switch (state)
    {
        case 0:
            m_board[x][y].setNormal();
            break;
        case -1:
            m_board[x][y].setBomb();
            break;
        case 1:
            m_board[x][y].setOpened();
            break;
        case 2:
            m_board[x][y].setFlag();
            break;
        case -2:
            m_board[x][y].setBomb();
            m_board[x][y].setFlag();
            break;
    }
}

void Board::LoadBoard(int opens, int flags, std::vector< std::vector<int> > board)
{
    m_cellsOpened = opens;
    m_cellsFlagged = flags;
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < m_columns; ++j)
            SetState(i, j, board[i][j]);
    SetBombNeighbors();
}