#include "BoardCell.h"

BoardCell::BoardCell(Rectangle rect)
{
    m_rect = rect;
    m_state = 0;
    m_bomb = false;
    m_opened = false;
    m_highlighted = false;
    m_revealed = false;
    m_bombNeighbors = 0;
}

int BoardCell::getCellDisplayContent()
{
    if (isRevealed())
    {
        if (isFlagged())
        {
            return (isBomb() ? CELL_FLAGGED : CELL_FLAGGED_WRONG);
        }
        else if (isBomb())
        {
            return (isOpened() ? CELL_BOMB_OPENED : CELL_BOMB);
        }
        else 
        {
            return (isOpened() ? CELL_NUM_EMPTY(getBombNeighbors()) : CELL_NOT_OPENED);
        }
    }
    else
    {
        if (isHighlighted())
        {
            return CELL_HIGHLIGHTED;
        }
        else if (isFlagged())
        {
            return CELL_FLAGGED;
        }
        else if (isOpened())
        {
            return (isBomb() ? CELL_BOMB_OPENED : CELL_NUM_EMPTY(getBombNeighbors()));
        }
        else
        {
            return CELL_NOT_OPENED;
        }
    }
}

void BoardCell::setBomb()
{
    m_bomb = true;
}

void BoardCell::setNormal()
{
    m_state = 0;
    m_opened = false;
    m_highlighted = false;
}

void BoardCell::setFlag()
{
    m_state = 1;
    m_opened = false;
    m_highlighted = false;
}

void BoardCell::setHighlight()
{
    m_opened = false;
    m_highlighted = true;
}

void BoardCell::setOpened()
{
    m_state = 0;
    m_opened = true;
    m_highlighted = false;
}

void BoardCell::setRevealed()
{
    m_revealed = true;
    m_highlighted = false;
}

void BoardCell::setDefault()
{
    m_opened = false;
    m_highlighted = false;
}

void BoardCell::setBombNeighbors(int bombNeighbors)
{
    m_bombNeighbors = bombNeighbors;
}

int BoardCell::leftClick()
{
    if (!isRevealed() && isHighlighted() && !isOpened() && !isFlagged()) return 1; // send command to open the cell
    return 0; // do nothing
}

int BoardCell::rightClick()
{
    if (!isRevealed() && isHighlighted())
    {
        if (isFlagged()) return 2; // send command to unflag cell
        else return 1; // send command to flag cell
    }
    return 0;
}

bool BoardCell::holdMouse()
{
    if (!isRevealed()) 
    {
        setHighlight();
        return 1;
    }
    return 0;
}

Rectangle BoardCell::getTextureOfCell(int cellState)
{
    return Rectangle{200.0f * cellState, 0, 200, 200};
}

void BoardCell::draw()
{
    Rectangle sourceRec = getTextureOfCell(getCellDisplayContent());
    DrawTexturePro(Assets::cellTexture, sourceRec, m_rect, Vector2{0, 0}, 0.0, WHITE);
}