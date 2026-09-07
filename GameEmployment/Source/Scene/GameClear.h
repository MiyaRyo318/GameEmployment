#pragma once

class GameClear
{
public:
    GameClear();

    void Init();
    void Update();
    void Draw();
    void End();

    // ƒ^ƒCƒgƒ‹‚É–ß‚é‚©
    bool IsReturnTitle() const;

private:

    bool m_ReturnTitle;
};