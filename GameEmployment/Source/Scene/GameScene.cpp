#include "GameScene.h"

GameScene::GameScene()
{
    m_StartTime = 0;
    m_CurrentTime = 0.0f;
}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
    // カメラ
    m_Camera.Init();

    // プレイヤー
    //m_Player.Init();

    // 敵
    //m_Enemy.Init();

    // ノーツ
    m_NoteManager.Init();

    // ゲーム開始時間
    m_StartTime = GetNowCount();
}

void GameScene::Update()
{
    // 経過時間(秒)
    m_CurrentTime = (GetNowCount() - m_StartTime) / 1000.0f;

    m_Camera.Update();

    //m_Player.Update();

    //m_Enemy.Update();

    m_Input.Update();

    m_NoteManager.Update(m_CurrentTime);
}

void GameScene::Draw()
{
    // ===== 3D =====

    //m_Player.Draw();

    //m_Enemy.Draw();

    // ===== 2D =====

    DrawFormatString(
        300,
        100,
        GetColor(255, 255, 255),
        "GameScene");

    m_NoteManager.Draw();
}

void GameScene::End()
{

}