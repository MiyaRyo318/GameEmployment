#pragma once

#include "GameScene.h"
#include "TitleScene.h"
#include "GameClear.h"
#include "GameOver.h"

enum SceneType
{
    TITLE,
    GAME,
    GAMECLEAR,
    GAMEOVER,
    RESULT,
    LOADING
};

class SceneManager
{
public:

    void Init();

    void Update();

    void Draw();

    void End();

    bool IsExit() const;

private:

    SceneType m_Scene;

    GameScene m_GameScene;

    TitleScene m_TitleScene;

    GameClear m_GameClear;

    GameOver m_GameOver;

    bool m_IsExit;

    // ローディング管理
    SceneType m_NextScene;
    int m_LoadingStartTime;

    // ローディング開始
    void StartLoading(SceneType nextScene);

    // ローディング更新
    void UpdateLoading();

};