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
    }
}

void SceneManager::End()
{
    m_TitleScene.End();

    m_GameScene.End();
}