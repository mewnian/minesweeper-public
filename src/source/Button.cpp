#include "Button.h"

Button::Button(Rectangle rect, Texture2D texture)
{
    m_rect = rect;
    m_disabled = false;
    m_highlighted = false;
    m_texture = texture;
}

Rectangle Button::getRect()
{
    return m_rect;
}

ClickState Button::CheckAction(Vector2& currentMousePosition)
{
    if (m_disabled) return NO_CLICK;
    if (!m_highlighted)
    {
        if (CheckCollisionPointRec(currentMousePosition, m_rect))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) 
            {
                m_highlighted = true;
                return HOLD_CLICK;
            }
        }
        return NO_CLICK;
    }
    else
    {
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            m_highlighted = false;
            if (CheckCollisionPointRec(currentMousePosition, m_rect))
            {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
                {
                    return LEFT_CLICK;
                }
                else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) 
                {
                    return RIGHT_CLICK;
                }
                else return HOLD_CLICK;
            }
            return NO_CLICK;
        }
        else 
        {
            m_highlighted = true;
            return HOLD_CLICK;
        }
    }    
    return NO_CLICK;
}

void Button::Draw()
{
    DrawTexturePro(m_texture, Rectangle{0, 0.5f * m_texture.height * (float)m_highlighted, (float)m_texture.width, 0.5f * m_texture.height}, m_rect, Vector2{0, 0}, 0.0, WHITE);
}