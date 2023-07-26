#include "IdempotentButton.h"

IdempotentButton::IdempotentButton(Rectangle rect, Texture2D texture):
    Button(rect, texture)
{
    m_state = false;
}

void IdempotentButton::Draw()
{
    DrawTexturePro(
        m_texture, 
        Rectangle{
            0.5f * m_texture.width * m_state, 
            0.5f * m_texture.height * (float)m_highlighted, 
            0.5f * m_texture.width, 
            0.5f * m_texture.height
        }, 
        m_rect, Vector2{0, 0}, 
        0.0, 
        WHITE
    );
}