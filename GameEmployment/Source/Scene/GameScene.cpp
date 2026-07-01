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

    m_Input.Update();

    m_Camera.Update();

    //m_Player.Update();

    //m_Enemy.Update();

    m_NoteManager.Update(m_CurrentTime);
}

void GameScene::Draw()
{
    // ===== 3D =====

    //m_Player.Draw();

    //m_Enemy.Draw();

    // ===== 2D =====

    // レーン
    DrawBox(
        0,
        460,
        1280,
        540,
        GetColor(60, 60, 60),
        TRUE);

    // 光る部分
    if (m_Input.IsDon())
    {
        DrawCircle(
            200,
            500,
            40,
            GetColor(255, 80, 80),
            TRUE);
    }

    if (m_Input.IsKa())
    {
        DrawCircle(
            200,
            500,
            40,
            GetColor(80, 160, 255),
            TRUE);
    }

    // 判定ライン
    DrawBox(
        198,
        460,
        202,
        540,
        GetColor(255, 255, 255),
        TRUE);

    // 判定枠
    DrawCircle(
        200,
        500,
        45,
        GetColor(255, 255, 255),
        FALSE);

    // ノーツ
    m_NoteManager.Draw();

    int judgeColor = GetColor(255, 255, 255);

    if (m_Input.IsDon())
    {
        judgeColor = GetColor(255, 0, 0);
    }
    else if (m_Input.IsKa())
    {
        judgeColor = GetColor(0, 128, 255);
    }

    DrawCircle(
        200,
        500,
        45,
        judgeColor,
        FALSE);

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