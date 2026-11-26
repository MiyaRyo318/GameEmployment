#include "GameScene.h"
#include "../Judge/JudgeManager.h"
#include "../Sound/Sound.h"
#include "../Sound/SE.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Skybox/Skybox.h"
#include "../Pause/Pause.h"

SE m_SE;

Skybox m_Skybox;

GameScene::GameScene()
{
    m_StartTime = 0;
    m_CurrentTime = 0.0f;
    m_AutoMoveTime = 0.0f;

    m_IsRetry = false;
    m_IsReturnTitle = false;
    m_BGMStarted = false;
    m_IsBranchRequested = false;

    m_IsWaitingStart = true;
    m_WaitStartTime = 0;

    m_Difficulty = 1;

    m_IsBranchSelecting = false;
    m_SelectedBranch = 0;
}

GameScene::~GameScene()
{

}

void GameScene::Init(int difficulty)
{
    m_Difficulty = difficulty;

    m_IsRetry = false;
    m_IsReturnTitle = false;

    // ポーズ初期化
    m_Pause.Init();

    m_LastJudge = NONE;

    // カメラ
    m_Camera.Init();

    m_Skybox.Init();

    // プレイヤー
    m_Player.Init();

    // 敵
    m_Enemy.Init();

    // ノーツ
    const char* scorePath = "Data/Score/test.txt";

    if (m_Difficulty == 0)
    {
        scorePath = "Data/Score/test_easy.txt";
    }
    else if (m_Difficulty == 2)
    {
        scorePath = "Data/Score/test_hard.txt";
    }

    m_NoteManager.Init(scorePath);

    m_BulletManager.Init();

    m_Sound.Init();
    m_SE.Init();

    // BGMはまだ再生しない
    m_BGMStarted = false;

    // 3秒間の開始待ち
    m_IsWaitingStart = true;
    m_WaitStartTime = GetNowCount();

    // ゲーム時間はまだ進めない
    m_StartTime = 0;
    m_CurrentTime = 0.0f;
    m_AutoMoveTime = 0.0f;

    m_CurrentTime = 0.0f;
    m_AutoMoveTime = 0.0f;

    m_IsBranchRequested = false;
    m_IsBranchSelecting = false;
    m_SelectedBranch = 0;

    m_IsBranchCountdown = false;
    m_BranchCountdownStart = 0;
    m_BranchPauseStart = 0;

    // 草原ステージ読み込み
    m_StageHandle = MV1LoadModel("Data/Skybox/Sougen.x");

    if (m_StageHandle != -1)
    {
        // 位置
        MV1SetPosition(m_StageHandle, VGet(-150, 50, -150));

        // 大きさを変更
        MV1SetScale(m_StageHandle, VGet(1.0f, 4.0f, 1.0f));

        // 回転
        MV1SetRotationXYZ(m_StageHandle, VGet(0, 0, 0));
    }
}

void GameScene::Update()
{
    m_Input.Update();

    // 分岐画面に入る
    if (m_IsBranchRequested && !m_IsBranchSelecting)
    {
        m_IsBranchSelecting = true;
        m_SelectedBranch = 0;

        // 停止時刻を記録
        m_BranchPauseStart = GetNowCount();

        // BGM停止
        m_Sound.StopBGM();
    }

    // 分岐選択中
    if (m_IsBranchSelecting)
    {
        // 左キー：Aルート
        if (m_Input.IsLeftTrigger())
        {
            m_SelectedBranch = 0;
        }

        // 右キー：Bルート
        if (m_Input.IsRightTrigger())
        {
            m_SelectedBranch = 1;
        }

        // SPACE：決定
        if (m_Input.IsSpaceTrigger())
        {
            m_IsBranchSelecting = false;

            // カウントダウン開始
            m_IsBranchCountdown = true;
            m_BranchCountdownStart = GetNowCount();
        }

        return;
    }

    // 3秒カウントダウン
    if (m_IsBranchCountdown)
    {
        int elapsed = GetNowCount() - m_BranchCountdownStart;

        if (elapsed >= 3000)
        {
            // 停止していた時間をゲーム時間から除外
            m_StartTime += GetNowCount() - m_BranchPauseStart;

            m_IsBranchCountdown = false;

            // BGM再開
            m_Sound.PlayBGM();
        }

        return;
    }

    // ポーズ開始・ポーズ中の処理
    if (m_Pause.IsPaused())
    {
        PauseResult result = m_Pause.Update(m_Input);

        switch (result)
        {
        case PauseResult::Resume:

            // ゲーム時間を再開
            m_StartTime = GetNowCount() - (int)(m_CurrentTime * 1000.0f);

            // BGM再開
            m_Sound.PlayBGM();

            break;

        case PauseResult::Retry:

            m_IsRetry = true;
            return;

        case PauseResult::ReturnTitle:

            m_IsReturnTitle = true;
            return;

        case PauseResult::None:
            break;
        }

        // ポーズ中はゲームの処理を進めない
        return;
    }

    // ポーズ開始判定
    if (!m_IsWaitingStart && m_Input.IsPauseTrigger())
    {
        m_Pause.Start();

        // BGM停止
        m_Sound.StopBGM();

        return;
    }

    // ゲーム開始前の待機処理
    if (m_IsWaitingStart)
    {
        if (GetNowCount() - m_WaitStartTime >= 3000)
        {
            // 待機終了
            m_IsWaitingStart = false;

            // BGM再生開始
            m_Sound.PlayBGM();
            m_BGMStarted = true;

            // ゲーム時間の計測開始
            m_StartTime = GetNowCount();
            m_CurrentTime = 0.0f;
        }

        // 待機中はゲーム処理を進めない
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

    bool don = m_Input.IsDonTrigger();
    bool ka = m_Input.IsKaTrigger();

    if (don || ka)
    {
        // 押したキーのSE
        if (don)
        {
            m_SE.PlayDon();
        }
        else
        {
            m_SE.PlayKa();
        }

        // 現在の一番手前のノーツを取得
        Note* note = m_NoteManager.GetJudgeNote();

        if (note)
        {
            bool canHit = false;

            if (note->GetType() == RENDAN)
            {
                float startTime = note->GetHitTime();
                float endTime = startTime + note->GetDuration();

                if (m_CurrentTime >= startTime &&
                    m_CurrentTime <= endTime)
                {
                    note->AddRendanHit();
                }
            }

            switch (note->GetType())
            {
            case DON:
                canHit = don;
                break;

            case KA:
                canHit = ka;
                break;

            case ORANGE:
            case GREEN:
                canHit = don || ka;
                break;

            case BRANCH:
                canHit = don || ka;
                break;
            }

            if (canHit)
            {
                JudgeType judge =
                    m_Judge.Judge(note->GetHitTime(), m_CurrentTime);

                switch (judge)
                {
                case PERFECT:

                    note->SetJudge(true);
                    m_LastJudge = PERFECT;

                    if (note->GetType() == ORANGE)
                    {
                        m_Enemy.Damage(30);
                    }
                    else if (note->GetType() == GREEN)
                    {
                        m_Player.Heal(30);
                    }
                    else if (note->GetType() == BRANCH)
                    {
                        m_IsBranchRequested = true;
                    }

                    break;

                case GREAT:

                    note->SetJudge(true);
                    m_LastJudge = GREAT;

                    if (note->GetType() == ORANGE)
                    {
                        m_Enemy.Damage(30);
                    }
                    else if (note->GetType() == GREEN)
                    {
                        m_Player.Heal(30);
                    }
                    else if (note->GetType() == BRANCH)
                    {
                        m_IsBranchRequested = true;
                    }

                    break;

                case GOOD:

                    note->SetJudge(true);
                    m_LastJudge = GOOD;

                    if (note->GetType() == ORANGE)
                    {
                        m_Enemy.Damage(30);
                    }
                    else if (note->GetType() == GREEN)
                    {
                        m_Player.Heal(30);
                    }
                    else if (note->GetType() == BRANCH)
                    {
                        m_IsBranchRequested = true;
                    }

                    break;

                case NONE:
                    break;

                case MISS:
                    break;
                }
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
    m_Skybox.Draw();

    // 草原ステージ描画
    if (m_StageHandle != -1)
    {
        MV1DrawModel(m_StageHandle);
    }

    m_Player.Draw();

    m_Enemy.Draw();

    //m_BulletManager.Draw();

    // レーン
    DrawBox(0,610,1600,690,GetColor(60, 60, 60),TRUE);

    if (m_Input.IsDon())
    {
        DrawCircle(200,650,40,GetColor(255, 80, 80),TRUE);
    }

    if (m_Input.IsKa())
    {
        DrawCircle(200,650,40,GetColor(80, 160, 255),TRUE);
    }

    // 判定ライン
    DrawBox(198,610,202,690,GetColor(255, 255, 255),TRUE);

    // 判定枠
    DrawCircle(200,650,45,GetColor(255, 255, 255),FALSE);

    // ノーツ
    if (!m_IsWaitingStart)
    {
        m_NoteManager.Draw();
    }

    int judgeColor = GetColor(255, 255, 255);

    if (m_Input.IsDonTrigger())
    {
        judgeColor = GetColor(255, 0, 0);
    }
    else if (m_Input.IsKa())
    {
        judgeColor = GetColor(0, 128, 255);
    }

    DrawCircle(200,650,40,judgeColor,FALSE);

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
        //DrawFormatString(20,50,GetColor(255, 255, 255),"Now : %.2f",m_CurrentTime);

        //DrawFormatString(20,70,GetColor(255, 255, 255),"Hit : %.2f",note->GetHitTime());

        //DrawFormatString(20,90,GetColor(255, 255, 255),"Diff : %.2f",fabs(note->GetHitTime() - m_CurrentTime));
    }

    // HPゲージ背景
    DrawBox(20,20,320,50,GetColor(80, 80, 80),TRUE);

    // HP
    DrawBox(20,20,20 + m_Player.GetHP() * 3,50,GetColor(0, 255, 0),TRUE);

    // 枠
    DrawBox(20,20,320,50,GetColor(255, 255, 255),FALSE);

    DrawFormatString(330,25,GetColor(255, 255, 255),"%d / 100",m_Player.GetHP());

    // HPゲージ背景
    DrawBox(1280,20,1580,50,GetColor(80, 80, 80),TRUE);

    // HP
    DrawBox(1280,20,1280 + m_Enemy.GetHP() * 3, 50,GetColor(255, 80, 80),TRUE);

    // 枠
    DrawBox(1280,20,1580,50, GetColor(255, 255, 255), FALSE);

    // HP表示
    DrawFormatString(1280,55,GetColor(255, 255, 255),"ENEMY HP : %d / 100",m_Enemy.GetHP());

    Note* debugNote = m_NoteManager.GetJudgeNote();

    // 分岐選択画面
    if (m_IsBranchSelecting)
    {
        DrawBox(400, 300, 1200, 600,GetColor(20, 20, 50), TRUE);

        DrawString(700, 350, "BRANCH SELECT",GetColor(255, 255, 0));

        // Aルート
        int colorA = (m_SelectedBranch == 0)? GetColor(255, 255, 0): GetColor(180, 180, 180);

        // Bルート
        int colorB = (m_SelectedBranch == 1)? GetColor(255, 255, 0): GetColor(180, 180, 180);

        DrawString(550, 450, "A ROUTE", colorA);
        DrawString(950, 450, "B ROUTE", colorB);

        DrawString(600, 540,"LEFT / RIGHT : SELECT",GetColor(255, 255, 255));

        DrawString(650, 570,"SPACE : DECIDE",GetColor(255, 255, 255));
    }

    // 再開カウントダウン
    if (m_IsBranchCountdown)
    {
        int elapsed = GetNowCount() - m_BranchCountdownStart;

        int count = (3000 - elapsed + 999) / 1000;

        if (count > 0)
        {
            DrawFormatString(750, 400,GetColor(255, 255, 0), "%d", count);
        }
    }

    // ポーズ画面
    m_Pause.Draw();

    if (m_StageHandle == -1)
    {
        DrawString(100, 100,
            "STAGE LOAD ERROR",
            GetColor(255, 0, 0));
    }
    else
    {
        DrawString(100, 100,
            "STAGE LOAD SUCCESS",
            GetColor(0, 255, 0));
    }
}

void GameScene::End()
{
    // BGMを停止
    m_Sound.StopBGM();

    m_Sound.End();
    m_SE.End();

    m_Enemy.End();

    if (m_StageHandle != -1)
    {
        MV1DeleteModel(m_StageHandle);
        m_StageHandle = -1;
    }
}

bool GameScene::IsGameClear() const
{
    return m_Enemy.IsDead();
}

bool GameScene::IsGameOver() const
{
    return m_Player.IsDead();
}

bool GameScene::IsBranchRequested() const
{
    return m_IsBranchRequested;
}

bool GameScene::IsRetry() const
{
    return m_IsRetry;
}

bool GameScene::IsReturnTitle() const
{
    return m_IsReturnTitle;
}