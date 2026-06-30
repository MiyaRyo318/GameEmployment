#pragma once

#include "GameScene.h"

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

    GameScene m_GameScene;
};