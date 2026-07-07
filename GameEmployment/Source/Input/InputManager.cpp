#include "InputManager.h"
#include "DxLib.h"

void InputManager::Update()
{
    // ‘OƒtƒŒ[ƒ€‚ğ•Û‘¶
    m_OldDon = m_Don;
    m_OldKa = m_Ka;

    // Œ»İ‚Ìó‘Ô
    m_Don = CheckHitKey(KEY_INPUT_F);
    m_Ka = CheckHitKey(KEY_INPUT_J);

    // ‰Ÿ‚µ‚½uŠÔ‚¾‚¯true
    m_DonTrigger = (m_Don && !m_OldDon);
    m_KaTrigger = (m_Ka && !m_OldKa);
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