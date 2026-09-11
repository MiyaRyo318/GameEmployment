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

private:

    bool m_ReturnTitle;
};