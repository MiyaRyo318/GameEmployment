#include "InputManager.h"
#include "DxLib.h"

void InputManager::Update()
{
    // ëOÉtÉåÅ[ÉÄÇÃèÛë‘Çï€ë∂

    m_OldDon = m_Don;
    m_OldKa = m_Ka;

    m_OldPause = m_Pause;

    m_OldUp = m_Up;
    m_OldDown = m_Down;

    m_OldEnter = m_Enter;

    m_OldLeft = m_Left;
    m_OldRight = m_Right;
    m_OldSpace = m_Space;

    // åªç›ÇÃèÛë‘
    
    m_Don = CheckHitKey(KEY_INPUT_F);
    m_Ka = CheckHitKey(KEY_INPUT_J);

    m_Pause = CheckHitKey(KEY_INPUT_ESCAPE);

    m_Up = CheckHitKey(KEY_INPUT_UP);
    m_Down = CheckHitKey(KEY_INPUT_DOWN);

    m_Enter = CheckHitKey(KEY_INPUT_SPACE);

    m_Left = CheckHitKey(KEY_INPUT_LEFT);
    m_Right = CheckHitKey(KEY_INPUT_RIGHT);
    m_Space = CheckHitKey(KEY_INPUT_SPACE);

    // âüÇµÇΩèuä‘
    
    m_DonTrigger = (m_Don && !m_OldDon);

    m_KaTrigger = (m_Ka && !m_OldKa);

    m_PauseTrigger = (m_Pause && !m_OldPause);

    m_UpTrigger = (m_Up && !m_OldUp);

    m_DownTrigger = (m_Down && !m_OldDown);

    m_EnterTrigger = (m_Enter && !m_OldEnter);

    m_LeftTrigger = (m_Left && !m_OldLeft);
    m_RightTrigger = (m_Right && !m_OldRight);
    m_SpaceTrigger = (m_Space && !m_OldSpace);
}

bool InputManager::IsDon() const
{
    return m_Don;
}

bool InputManager::IsKa() const
{
    return m_Ka;
}

bool InputManager::IsDonTrigger() const
{
    return m_DonTrigger;
}

bool InputManager::IsKaTrigger() const
{
    return m_KaTrigger;
}

bool InputManager::IsPauseTrigger() const
{
    return m_PauseTrigger;
}

bool InputManager::IsUpTrigger() const
{
    return m_UpTrigger;
}

bool InputManager::IsDownTrigger() const
{
    return m_DownTrigger;
}

bool InputManager::IsEnterTrigger() const
{
    return m_EnterTrigger;
}

bool InputManager::IsLeftTrigger() const
{
    return m_LeftTrigger;
}

bool InputManager::IsRightTrigger() const
{
    return m_RightTrigger;
}

bool InputManager::IsSpaceTrigger() const
{
    return m_EnterTrigger;
}