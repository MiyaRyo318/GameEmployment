#include "GameScene.h"
#include "../Judge/JudgeManager.h"
#include "../Sound/Sound.h"
#include "../Sound/SE.h"
#include "../Player/Player.h"

SE m_SE;

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
    // ÉJÉÅÉâ
    m_Camera.Init();

    // ÉvÉåÉCÉÑÅ[
    m_Player.Init();

    // ìG
    //m_Enemy.Init();

    // ÉmÅ[Éc
    m_NoteManager.Init();

    m_Sound.Init();
    m_SE.Init();

    m_Sound.PlayBGM();

    // ÉQÅ[ÉÄäJénéûä‘
    m_StartTime = GetNowCount();
}

void GameScene::Update()
{
    // åoâﬂéûä‘(ïb)
    m_CurrentTime = (GetNowCount() - m_StartTime) / 1000.0f;

    m_Input.Update();

    if (m_Input.IsDonTrigger())
    {
        m_SE.PlayDon();

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
        m_SE.PlayKa();

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

        m_Player.Damage(10);
    }

    if (m_Player.IsDead())
    {
        // GameOverSceneÇ÷
    }

    m_NoteManager.Update(m_CurrentTime);
}

void GameScene::Draw()
{
    // ===== 3D =====

    //m_Player.Draw();

    //m_Enemy.Draw();

    // ===== 2D =====

    // ÉåÅ[Éì
    DrawBox(
        0,
        610,
        1600,
        690,
        GetColor(60, 60, 60),
        TRUE);

    if (m_Input.IsDon())
    {
        
        DrawCircle(
            200,
            650,
            40,
            GetColor(255, 80, 80),
            TRUE);
    }

    if (m_Input.IsKa())
    {
        DrawCircle(
            200,
            650,
            40,
            GetColor(80, 160, 255),
            TRUE);
    }

    // îªíËÉâÉCÉì
    DrawBox(
        198,
        610,
        202,
        690,
        GetColor(255, 255, 255),
        TRUE);

    // îªíËògÇ‚ÅBéüÇÃ‚Wâ@â∆ìñéÂÇÕâ¥Ç‚ÅB
    DrawCircle(
        200,
        650,
        45,
        GetColor(255, 255, 255),
        FALSE);

    // ÉmÅ[Éc
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
        650,
        40,
        judgeColor,
        FALSE);

    //DrawFormatString(300,100,GetColor(255, 255, 255),"GameScene");

    //m_NoteManager.Draw();

    switch (m_LastJudge)
    {
    case PERFECT:
        DrawString(185, 550, "PERFECT", GetColor(255, 255, 0));
        break;

    case GREAT:
        DrawString(185, 550, "GREAT", GetColor(0, 255, 0));
        break;

    case GOOD:
        DrawString(185, 550, "GOOD", GetColor(0, 255, 255));
        break;

    case MISS:
        DrawString(185, 550, "MISS", GetColor(255, 0, 0));
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

    // HPÉQÅ[ÉWîwåi
    DrawBox(
        20,
        20,
        320,
        50,
        GetColor(80, 80, 80),
        TRUE);

    // HP
    DrawBox(
        20,
        20,
        20 + m_Player.GetHP() * 3,
        50,
        GetColor(0, 255, 0),
        TRUE);

    // òg
    DrawBox(
        20,
        20,
        320,
        50,
        GetColor(255, 255, 255),
        FALSE);

    DrawFormatString(
        330,
        25,
        GetColor(255, 255, 255),
        "%d / 100",
        m_Player.GetHP());
}

void GameScene::End()
{
    m_Sound.End();
    m_SE.End();
}