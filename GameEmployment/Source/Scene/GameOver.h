#pragma once

class GameOver
{
public:
    GameOver();

    void Init();
    void Update();
    void Draw();
    void End();

    bool IsReturnTitle() const;
    bool IsRetry() const;

private:
    int m_Select;
    bool m_Retry;
    bool m_ReturnTitle;

    bool m_OldUp;
    bool m_OldDown;
    bool m_OldEnter;
};