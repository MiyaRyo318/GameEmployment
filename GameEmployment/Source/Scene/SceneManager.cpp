#include "SceneManager.h"
#include <cstdlib>

void SceneManager::Init()
{
    // とりあえずゲームシーンから開始や。
    m_Scene = TITLE;

    m_TitleScene.Init();
}

void SceneManager::Update()
{
    switch (m_Scene)
    {
    case TITLE:

        m_TitleScene.Update();

        if (m_TitleScene.IsStart())
        {
            m_GameScene.Init();

            m_Scene = GAME;
        }
        else if (m_TitleScene.IsExitGame())
        {
            // ゲーム終了
            DxLib_End();
            exit(0);
        }

        break;

    case GAME:

        m_GameScene.Update();

        // リトライ
        if (m_GameScene.IsRetry())
        {
            m_GameScene.End();

            m_GameScene.Init();
        }
        // タイトルに戻る
        else if (m_GameScene.IsReturnTitle())
        {
            m_GameScene.End();

            m_TitleScene.Init();

            m_Scene = TITLE;
        }
        // ゲームクリア
        else if (m_GameScene.IsGameClear())
        {
            m_GameScene.End();

            m_GameClear.Init();

            m_Scene = GAMECLEAR;
        }
        // ゲームオーバー
        else if (m_GameScene.IsGameOver())
        {
            m_GameScene.End();

            m_GameOver.Init();

            m_Scene = GAMEOVER;
        }

        break;

    case GAMECLEAR:

        m_GameClear.Update();

        if (m_GameClear.IsReturnTitle())
        {
            m_Scene = TITLE;
            m_TitleScene.Init();
        }

        break;

    case GAMEOVER:

        m_GameOver.Update();

        if (m_GameOver.IsReturnTitle())
        {
            m_Scene = TITLE;
            m_TitleScene.Init();
        }

        break;
    }
}

void SceneManager::Draw()
{
    switch (m_Scene)
    {
    case TITLE:

        m_TitleScene.Draw();

        break;

    case GAME:

        m_GameScene.Draw();

        break;

    case GAMECLEAR:

        m_GameClear.Draw();

        break;

    case GAMEOVER:

        m_GameOver.Draw();

        break;
    }
}

void SceneManager::End()
{
    m_TitleScene.End();

    m_GameScene.End();

    m_GameClear.End();

    m_GameOver.End();
}