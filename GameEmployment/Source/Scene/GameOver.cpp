#include "GameOver.h"
#include "DxLib.h"

GameOver::GameOver()
{
    m_Select = 0;
    m_Retry = false;
    m_ReturnTitle = false;

    m_OldUp = false;
    m_OldDown = false;
    m_OldEnter = false;
}

void GameOver::Init()
{
    // 初期選択はリトライ
    m_Select = 0;

    m_Retry = false;
    m_ReturnTitle = false;

    m_OldUp = false;
    m_OldDown = false;
    m_OldEnter = false;
}

void GameOver::Update()
{
    bool up = CheckHitKey(KEY_INPUT_UP) != 0;
    bool down = CheckHitKey(KEY_INPUT_DOWN) != 0;
    bool enter = CheckHitKey(KEY_INPUT_RETURN) != 0;

    // 上下キーで選択変更
    if (up && !m_OldUp)
    {
        m_Select--;

        if (m_Select < 0)
        {
            m_Select = 1;
        }
    }

    if (down && !m_OldDown)
    {
        m_Select++;

        if (m_Select > 1)
        {
            m_Select = 0;
        }
    }

    // ENTERキーで決定
    if (enter && !m_OldEnter)
    {
        if (m_Select == 0)
        {
            m_Retry = true;
        }
        else
        {
            m_ReturnTitle = true;
        }
    }

    m_OldUp = up;
    m_OldDown = down;
    m_OldEnter = enter;
}

void GameOver::Draw()
{
    // 背景
    DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);

    // GAME OVER
    DrawString(650, 350, "GAME OVER",GetColor(255, 0, 0));

    // 選択項目
    if (m_Select == 0)
    {
        DrawString(650, 450, "> リトライ",GetColor(255, 255, 0));

        DrawString(650, 500, "  タイトルに戻る",GetColor(255, 255, 255));
    }
    else
    {
        DrawString(650, 450, "  リトライ",GetColor(255, 255, 255));

        DrawString(650, 500, "> タイトルに戻る",GetColor(255, 255, 0));
    }

    DrawString(650, 570, "Up / Down : 選択",GetColor(200, 200, 200));

    DrawString(650, 600, "Enter : 決定",GetColor(200, 200, 200));
}

void GameOver::End()
{
}

bool GameOver::IsReturnTitle() const
{
    return m_ReturnTitle;
}

bool GameOver::IsRetry() const
{
    return m_Retry;
}