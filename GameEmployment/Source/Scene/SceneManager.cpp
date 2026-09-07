#include "SceneManager.h"

void SceneManager::Init()
{
    // とりあえずゲームシーンから開始
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

        break;

    case GAME:

        m_GameScene.Update();

        if (m_GameScene.IsGameClear())
        {
            m_GameClear.Init();
            m_Scene = GAMECLEAR;
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
    }
}

void SceneManager::End()
{
    m_TitleScene.End();

    m_GameScene.End();

    m_GameClear.End();
}