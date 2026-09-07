#pragma once

#include "GameScene.h"
#include "TitleScene.h"
#include "GameClear.h"

enum SceneType
{
    TITLE,
    GAME,
    GAMECLEAR,
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

    TitleScene m_TitleScene;

    GameClear m_GameClear;
};