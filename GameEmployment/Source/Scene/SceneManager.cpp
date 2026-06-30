#include "SceneManager.h"

void SceneManager::Init()
{
    // とりあえずゲームシーンから開始
    m_Scene = GAME;

    m_GameScene.Init();
}

void SceneManager::Update()
{
    switch (m_Scene)
    {
    case GAME:
        m_GameScene.Update();
        break;
    }
}

void SceneManager::Draw()
{
    switch (m_Scene)
    {
    case GAME:
        m_GameScene.Draw();
        break;
    }
}

void SceneManager::End()
{
    m_GameScene.End();
}