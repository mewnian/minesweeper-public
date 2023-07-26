#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "Global.h"

class Button
{
protected:
    Rectangle m_rect;
    bool m_disabled;
    bool m_highlighted;
    Texture2D m_texture;
public:
    Button(Rectangle rect, Texture2D texture);
    Rectangle getRect();
    ClickState CheckAction(Vector2& currentMousePosition);
    void Draw();
};

#endif