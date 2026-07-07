#pragma once

class InputManager
{
public:

    void Update();

    bool IsDon() const;
    bool IsKa() const;

    bool IsDonTrigger() const;
    bool IsKaTrigger() const;

private:

    bool m_Don = false;
    bool m_Ka = false;

    bool m_OldDon = false;
    bool m_OldKa = false;

    bool m_DonTrigger = false;
    bool m_KaTrigger = false;
};