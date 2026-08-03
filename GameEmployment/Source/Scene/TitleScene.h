#pragma once

class TitleScene
{
public:

    void Init();

    void Update();

    void Draw();

    void End();

    bool IsStart() const;

private:

    bool m_IsStart = false;

    int m_TitleImage = -1;
};