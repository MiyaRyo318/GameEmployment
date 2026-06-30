#pragma once

class InputManager
{
public:

    void Update();

    bool IsDon() const;

    bool IsKa() const;

private:

    bool m_Don;

    bool m_Ka;
};