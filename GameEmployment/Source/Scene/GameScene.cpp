#include "GameScene.h"
#include "../Judge/JudgeManager.h"
#include "../Sound/Sound.h"
#include "../Sound/SE.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Skybox/Skybox.h"

SE m_SE;

Skybox m_Skybox;

GameScene::GameScene()
{
    m_StartTime = 0;
    m_CurrentTime = 0.0f;
    m_AutoMoveTime = 0.0f;

    m_IsPaused = false;
    m_PauseSelect = 0;

    m_IsRetry = false;
    m_IsReturnTitle = false;

    m_BGMStarted = false;
}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
    // ポーズ状態を初期化
    m_IsPaused = false;
    m_PauseSelect = 0;

    m_IsRetry = false;
    m_IsReturnTitle = false;

    m_LastJudge = NONE;

    // カメラ
    m_Camera.Init();

    m_Skybox.Init();

    // プレイヤー
    m_Player.Init();

    // 敵
    m_Enemy.Init();

    // ノーツ
    m_NoteManager.Init();

    m_BulletManager.Init();

    m_Sound.Init();
    m_SE.Init();

    m_Sound.PlayBGM();

    m_BGMStarted = true;

    // ゲーム開始時間
    m_StartTime = GetNowCount();

    m_CurrentTime = 0.0f;
    m_AutoMoveTime = 0.0f;
}

void GameScene::Update()
{
    m_Input.Update();

    // =========================
    // ポーズ開始
    // =========================

    if (!m_IsPaused)
    {
        if (m_Input.IsPauseTrigger())
        {
            m_IsPaused = true;

            // 初期選択は「再開」
            m_PauseSelect = 0;

            // BGM停止
            m_Sound.StopBGM();

            return;
        }
    }

    // =========================
    // ポーズ中
    // =========================

    if (m_IsPaused)
    {
        // ESCで再開
        if (m_Input.IsPauseTrigger())
        {
            m_IsPaused = false;

            m_StartTime =
                GetNowCount()
                - (int)(m_CurrentTime * 1000.0f);

            m_Sound.PlayBGM();

            return;
        }

        // 上
        if (m_Input.IsUpTrigger())
        {
            m_PauseSelect--;

            if (m_PauseSelect < 0)
            {
                m_PauseSelect = 2;
            }
        }

        // 下
        if (m_Input.IsDownTrigger())
        {
            m_PauseSelect++;

            if (m_PauseSelect > 2)
            {
                m_PauseSelect = 0;
            }
        }

        // 決定
        if (m_Input.IsEnterTrigger())
        {
            if (m_PauseSelect == 0)
            {
                // 再開
                m_IsPaused = false;

                m_StartTime =
                    GetNowCount()
                    - (int)(m_CurrentTime * 1000.0f);

                m_Sound.PlayBGM();
            }
            else if (m_PauseSelect == 1)
            {
                // リトライ
                m_IsRetry = true;
                return;
            }
            else if (m_PauseSelect == 2)
            {
                // タイトルに戻る
                m_IsReturnTitle = true;
                return;
            }
        }

        return;
    }

    // 経過時間(秒)
    m_CurrentTime = (GetNowCount() - m_StartTime) / 1000.0f;

    if (m_BGMStarted && m_Sound.IsBGMFinished())
    {
        m_Sound.StopBGM();

        // 曲終了 = ゲームクリア
        m_Enemy.Damage(m_Enemy.GetHP());

        return;
    }

    if (m_Input.IsDonTrigger())
    {
        m_SE.PlayDon();

        Note* note = m_NoteManager.GetJudgeNote(DON);

        if (note)
        {
            JudgeType judge =m_Judge.Judge(note->GetHitTime(),m_CurrentTime);

            switch (judge)
            {
            case PERFECT:

                note->SetJudge(true);m_LastJudge = PERFECT;

                m_BulletManager.ShootPlayerBullet(m_Player.GetPosition());

                break;

            case GREAT:
                
                note->SetJudge(true);m_LastJudge = GREAT;

                m_BulletManager.ShootPlayerBullet(m_Player.GetPosition());

                break;

            case GOOD:

                note->SetJudge(true);
                m_LastJudge = GOOD;

                m_BulletManager.ShootPlayerBullet(
                    m_Player.GetPosition());

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

                m_BulletManager.ShootPlayerBullet(
                    m_Player.GetPosition());

                break;

            case GREAT:

                note->SetJudge(true);
                m_LastJudge = GREAT;

                m_BulletManager.ShootPlayerBullet(
                    m_Player.GetPosition());

                break;

            case GOOD:

                note->SetJudge(true);
                m_LastJudge = GOOD;

                m_BulletManager.ShootPlayerBullet(
                    m_Player.GetPosition());

                break;

            case NONE:
                break;

            case MISS:
                break;
            }
        }
    }

    m_Camera.Update();

    m_Skybox.Update();

    // プレイヤーの手動操作は停止
    // m_Player.Update();

    // プレイヤーを自動移動
    m_Player.AutoMove(1.0f / 60.0f);

    // 敵も自動移動させる場合
    m_Enemy.AutoMove(1.0f / 60.0f);

    if (m_Enemy.CanShoot())
    {
        //m_BulletManager.ShootEnemyBullet(m_Enemy.GetPosition(),m_Enemy.GetAttackLane());
    }

    //m_BulletManager.Update();

    //m_BulletManager.CheckEnemyCollision(m_Enemy);

    //m_BulletManager.CheckPlayerCollision(m_Player);

    if (m_NoteManager.AutoMiss(m_CurrentTime))
    {
        m_LastJudge = MISS;

        m_Player.Damage(10);
    }

    if (m_Player.IsDead())
    {
        // GameOverSceneへ
    }

    m_NoteManager.Update(m_CurrentTime);
}

void GameScene::Draw()
{
    // ===== 3D =====

    m_Skybox.Draw();

    m_Player.Draw();

    m_Enemy.Draw();

    //m_BulletManager.Draw();

    // ===== 2D =====

    // レーン
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

    // 判定ライン
    DrawBox(
        198,
        610,
        202,
        690,
        GetColor(255, 255, 255),
        TRUE);

    // 判定枠や。次の禪院家当主は俺や。
    DrawCircle(
        200,
        650,
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

    // HPゲージ背景
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

    // 枠
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

    // HPゲージ背景
    //DrawBox(1280,20,1580,50,GetColor(80, 80, 80),TRUE);

    // HP
    //DrawBox(1280,20,1280 + m_Enemy.GetHP() * 3, 50,GetColor(255, 80, 80),TRUE);

    // 枠
    //DrawBox(1280,20,1580,50, GetColor(255, 255, 255), FALSE);

    // HP表示
    //DrawFormatString(1280,55,GetColor(255, 255, 255),"ENEMY HP : %d / 100",m_Enemy.GetHP());

    // =========================
// ポーズ画面
// =========================

    if (m_IsPaused)
    {
        // 画面を暗くする
        SetDrawBlendMode(
            DX_BLENDMODE_ALPHA,
            180);

        DrawBox(
            0,
            0,
            1600,
            900,
            GetColor(0, 0, 0),
            TRUE);

        SetDrawBlendMode(
            DX_BLENDMODE_NOBLEND,
            0);

        int white =
            GetColor(255, 255, 255);

        int yellow =
            GetColor(255, 255, 0);

        // PAUSE
        DrawString(
            760,
            180,
            "PAUSE",
            white);

        // メニュー
        int resumeColor = white;
        int retryColor = white;
        int titleColor = white;

        if (m_PauseSelect == 0)
        {
            resumeColor = yellow;
        }
        else if (m_PauseSelect == 1)
        {
            retryColor = yellow;
        }
        else if (m_PauseSelect == 2)
        {
            titleColor = yellow;
        }

        DrawString(
            700,
            350,
            "再開",
            resumeColor);

        DrawString(
            700,
            420,
            "リトライ",
            retryColor);

        DrawString(
            700,
            490,
            "タイトルに戻る",
            titleColor);

        DrawFormatString(580, 780, GetColor(255, 255, 255),
            "↑ / ↓：選択    SPACE：決定    ESC：再開");
    }
}

void GameScene::End()
{
    // BGMを停止
    m_Sound.StopBGM();

    m_Sound.End();
    m_SE.End();

    m_Enemy.End();
}

bool GameScene::IsGameClear() const
{
    return m_Enemy.IsDead();
}

bool GameScene::IsGameOver() const
{
    return m_Player.IsDead();
}

bool GameScene::IsRetry() const
{
    return m_IsRetry;
}

bool GameScene::IsReturnTitle() const
{
    return m_IsReturnTitle;
}