#include "InputManager.h"
#include "DxLib.h"

void InputManager::Update()
{
    // ‘OƒtƒŒ[ƒ€‚Ìó‘Ô‚ğ•Û‘¶

    m_OldDon = m_Don;
    m_OldKa = m_Ka;

    m_OldPause = m_Pause;

    m_OldUp = m_Up;
    m_OldDown = m_Down;

    m_OldEnter = m_Enter;

    // Œ»İ‚Ìó‘Ô
    
    m_Don = CheckHitKey(KEY_INPUT_F);
    m_Ka = CheckHitKey(KEY_INPUT_J);

    m_Pause = CheckHitKey(KEY_INPUT_ESCAPE);

    m_Up = CheckHitKey(KEY_INPUT_UP);
    m_Down = CheckHitKey(KEY_INPUT_DOWN);

    m_Enter = CheckHitKey(KEY_INPUT_SPACE);

    // ‰Ÿ‚µ‚½uŠÔ
    
    m_DonTrigger =
        (m_Don && !m_OldDon);

    m_KaTrigger =
        (m_Ka && !m_OldKa);

    m_PauseTrigger =
        (m_Pause && !m_OldPause);

    m_UpTrigger =
        (m_Up && !m_OldUp);

    m_DownTrigger =
        (m_Down && !m_OldDown);

    m_EnterTrigger =
        (m_Enter && !m_OldEnter);
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