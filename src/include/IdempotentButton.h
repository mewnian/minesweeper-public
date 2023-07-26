#ifndef IDEMPOTENT_BUTTON_H
#define IDEMPOTENT_BUTTON_H

#include "raylib.h"
#include "Button.h"

class IdempotentButton: public Button
{
private:
    bool m_state;
public:
    IdempotentButton(Rectangle rect, Texture2D texture);
    void SetTrue() { m_state = true; }
    void SetFalse() { m_state = false; }
    void ToggleState() { m_state = !m_state; }
    bool GetState() { return m_state; }
    void Draw();
};

#endif