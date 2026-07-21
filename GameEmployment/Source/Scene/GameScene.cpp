#include "GameScene.h"
#include "../Judge/JudgeManager.h"
#include "../Sound/Sound.h"

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

    m_Sound.Init();

    //m_Sound.PlayBGM();

    // ゲーム開始時間
    m_StartTime = GetNowCount();
}

void GameScene::Update()
{
    // 経過時間(秒)
    m_CurrentTime = (GetNowCount() - m_StartTime) / 1000.0f;

    m_Input.Update();

    if (m_Input.IsDonTrigger())
    {
        Note* note = m_NoteManager.GetJudgeNote(DON);

        if (note)
        {
            JudgeType judge =
                m_Judge.Judge(
                    note->GetHitTime(),
                    m_CurrentTime);

            switch (judge)
            {
            case PERFECT:

                note->SetJudge(true);
                m_LastJudge = PERFECT;
                break;

            case GREAT:

                note->SetJudge(true);
                m_LastJudge = GREAT;
                break;

            case GOOD:

                note->SetJudge(true);
                m_LastJudge = GOOD;
                break;

            case NONE:
                break;

            case MISS:
                break;
            }
        }
    }

    if (m_Input.IsKaTrigger())
    {
        Note* note = m_NoteManager.GetJudgeNote(KA);

        if (note)
        {
            JudgeType judge =
                m_Judge.Judge(
                    note->GetHitTime(),
                    m_CurrentTime);

            switch (judge)
            {
            case PERFECT:
                note->SetJudge(true);
                m_LastJudge = PERFECT;
                break;

            case GREAT:
                note->SetJudge(true);
                m_LastJudge = GREAT;
                break;

            case GOOD:
                note->SetJudge(true);
                m_LastJudge = GOOD;
                break;

            case NONE:
                break;

            case MISS:
                break;
            }
        }
    }

    m_Camera.Update();

    //m_Player.Update();

    //m_Enemy.Update();

    if (m_NoteManager.AutoMiss(m_CurrentTime))
    {
        m_LastJudge = MISS;
    }

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

    if (m_Input.IsDonTrigger())
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

    //DrawFormatString(300,100,GetColor(255, 255, 255),"GameScene");

    //m_NoteManager.Draw();

    switch (m_LastJudge)
    {
    case PERFECT:
        DrawString(500, 100, "PERFECT", GetColor(255, 255, 0));
        break;

    case GREAT:
        DrawString(500, 100, "GREAT", GetColor(0, 255, 0));
        break;

    case GOOD:
        DrawString(500, 100, "GOOD", GetColor(0, 255, 255));
        break;

    case MISS:
        DrawString(500, 100, "MISS", GetColor(255, 0, 0));
        break;
    }

    Note* note = m_NoteManager.GetFirstNote();

    if (note)
    {
        DrawFormatString(
            20,
            50,
            GetColor(255, 255, 255),
            "Now : %.2f",
            m_CurrentTime);

        DrawFormatString(
            20,
            70,
            GetColor(255, 255, 255),
            "Hit : %.2f",
            note->GetHitTime());

        DrawFormatString(
            20,
            90,
            GetColor(255, 255, 255),
            "Diff : %.2f",
            fabs(note->GetHitTime() - m_CurrentTime));
    }
}

void GameScene::End()
{
    m_Sound.End();
}