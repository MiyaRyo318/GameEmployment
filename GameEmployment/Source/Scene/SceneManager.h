#pragma once

enum SceneType
{
    TITLE,
    GAME,
    RESULT
};


class SceneManager
{

public:

    void Init();

    void Update();

    void Draw();

    void End();


private:

    SceneType m_Scene;

};