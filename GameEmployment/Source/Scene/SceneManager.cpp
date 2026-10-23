#include "SceneManager.h"
#include "DxLib.h"
#include "TitleScene.h"

constexpr int LOADING_TIME = 1500; // ローディング時間：1.5秒

void SceneManager::Init()
{
    m_IsExit = false;
    m_Scene = TITLE;
    m_NextScene = TITLE;
    m_LoadingStartTime = 0;

    m_TitleScene.Init();

    m_SelectedDifficulty = 1;
}

// ローディング開始
void SceneManager::StartLoading(SceneType nextScene)
{
    m_NextScene = nextScene;
    m_LoadingStartTime = GetNowCount();
    m_Scene = LOADING;
}

// ローディング更新
void SceneManager::UpdateLoading()
{
    if (GetNowCount() - m_LoadingStartTime < LOADING_TIME)
    {
        return;
    }

    // ローディング終了後、遷移先を初期化
    switch (m_NextScene)
    {
    case TITLE:
        m_TitleScene.Init();
        break;

    case GAME:
        m_GameScene.Init(m_SelectedDifficulty);
        break;

    case GAMECLEAR:
        m_GameClear.Init();
        break;

    case GAMEOVER:
        m_GameOver.Init();
        break;

    default:
        break;
    }

    m_Scene = m_NextScene;
}

void SceneManager::Update()
{
    switch (m_Scene)
    {
    case TITLE:
        m_TitleScene.Update();

        // ゲーム終了が選択されたら終了フラグを立てる
        if (m_TitleScene.IsExitGame())
        {
            m_IsExit = true;
            break;
        }

        if (m_TitleScene.IsStart())
        {
            m_SelectedDifficulty = m_TitleScene.GetDifficultySelect();

            StartLoading(GAME);
        }
        break;

    case GAME:
        m_GameScene.Update();

        // リトライ
        if (m_GameScene.IsRetry())
        {
            m_GameScene.End();
            StartLoading(GAME);
        }
        // タイトルに戻る
        else if (m_GameScene.IsReturnTitle())
        {
            m_GameScene.End();
            StartLoading(TITLE);
        }
        // ゲームクリア
        else if (m_GameScene.IsGameClear())
        {
            m_GameScene.End();
            StartLoading(GAMECLEAR);
        }
        // ゲームオーバー
        if (m_GameScene.IsGameOver())
        {
            m_GameScene.End();
            m_GameOver.Init();
            m_Scene = GAMEOVER;
        }
        break;


    case GAMECLEAR:
        m_GameClear.Update();

        // リトライ
        if (m_GameClear.IsRetry())
        {
            m_GameClear.End();
            StartLoading(GAME);
        }
        // タイトルに戻る
        else if (m_GameClear.IsReturnTitle())
        {
            m_GameClear.End();
            StartLoading(TITLE);
        }
        break;

    case GAMEOVER:
        m_GameOver.Update();

        // リトライ
        if (m_GameOver.IsRetry())
        {
            m_GameOver.End();
            StartLoading(GAME);
        }
        // タイトルに戻る
        else if (m_GameOver.IsReturnTitle())
        {
            m_GameOver.End();
            StartLoading(TITLE);
        }
        break;

    case LOADING:
        UpdateLoading();
        break;

    case RESULT:
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

    case LOADING:
    {
        // 背景
        DrawBox(0, 0, 1600, 900, GetColor(5, 8, 20), TRUE);

        // タイトル文字
        DrawString(720, 370, "LOADING...", GetColor(255, 255, 255));

        // 進捗バーの背景
        int barX = 500;
        int barY = 440;
        int barWidth = 600;
        int barHeight = 20;

        DrawBox(barX, barY,barX + barWidth, barY + barHeight,GetColor(60, 60, 75), TRUE);

        // 経過時間に合わせてバーを伸ばす
        int elapsed = GetNowCount() - m_LoadingStartTime;
        float progress = (float)elapsed / LOADING_TIME;

        if (progress > 1.0f)
        {
            progress = 1.0f;
        }

        int progressWidth = (int)(barWidth * progress);

        DrawBox(barX, barY,barX + progressWidth, barY + barHeight,GetColor(0, 200, 255), TRUE);

        break;
    }

    case RESULT:
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

bool SceneManager::IsExit() const
{
    return m_IsExit;
}