#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include "raylib.h"
#include "Global.h"

class BoardCell
{
private:
    Rectangle m_rect{};
    int m_state;
    // 0 - closed, 1 - flagged
    bool m_bomb;
    bool m_opened;
    bool m_highlighted;
    bool m_revealed;
    // opened = in-game, revealed = game over
    int m_bombNeighbors;
public:
    BoardCell(Rectangle rect = Rectangle{0,0,0,0});
    Rectangle getRect() { return m_rect; }
    int getState() { return m_state; }
    bool isHighlighted() { return m_highlighted; }
    bool isBomb() { return m_bomb; }
    bool isOpened() { return m_opened; }
    bool isFlagged() { return m_state == 1; }
    bool isRevealed() { return m_revealed; }
    int getBombNeighbors() { return m_bombNeighbors; }
    int getCellDisplayContent();
    void setBomb();
    void setNormal();
    void setFlag();
    void setHighlight();
    void setOpened();
    void setRevealed();
    void setDefault();
    void setBombNeighbors(int bombNeighbors);
    int leftClick();
    int rightClick();
    bool holdMouse();
    Rectangle getTextureOfCell(int cellState);
    void draw();
};

#endif