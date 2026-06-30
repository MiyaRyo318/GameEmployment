#include "InputManager.h"
#include "DxLib.h"

void InputManager::Update()
{
    m_Don = CheckHitKey(KEY_INPUT_F);

    m_Ka = CheckHitKey(KEY_INPUT_J);
}

bool InputManager::IsDon() const
{
    return m_Don;
}

bool InputManager::IsKa() const
{
    return m_Ka;
}