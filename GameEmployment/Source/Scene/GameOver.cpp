#include "GameOver.h"
#include "DxLib.h"

GameOver::GameOver()
{
    m_Select = 0;
    m_ReturnTitle = false;
    m_Retry = false;

    m_OldUp = false;
    m_OldDown = false;
    m_OldSpace = false;
}

void GameOver::Init()
{
    m_Select = 0;
    m_ReturnTitle = false;
    m_Retry = false;

    m_OldUp = false;
    m_OldDown = false;
    m_OldSpace = false;
}

void GameOver::Update()
{
    bool up = CheckHitKey(KEY_INPUT_UP) != 0;
    bool down = CheckHitKey(KEY_INPUT_DOWN) != 0;
    bool space = CheckHitKey(KEY_INPUT_SPACE) != 0;

    if (up && !m_OldUp)
    {
        m_Select--;
        if (m_Select < 0)
            m_Select = 1;
    }

    if (down && !m_OldDown)
    {
        m_Select++;
        if (m_Select > 1)
            m_Select = 0;
    }

    if (space && !m_OldSpace)
    {
        if (m_Select == 0)
            m_Retry = true;
        else
            m_ReturnTitle = true;
    }

    m_OldUp = up;
    m_OldDown = down;
    m_OldSpace = space;
}

void GameOver::Draw()
{
    DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);

    DrawString(650, 350, "GAME OVER", GetColor(255, 0, 0));

    DrawString(650, 450,m_Select == 0 ? "> リトライ" : "  リトライ",m_Select == 0 ? GetColor(255, 255, 0) : GetColor(255, 255, 255));

    DrawString(650, 500,m_Select == 1 ? "> タイトルに戻る" : "  タイトルに戻る",m_Select == 1 ? GetColor(255, 255, 0) : GetColor(255, 255, 255));

    DrawString(650, 570, "UP / DOWN : 選択", GetColor(200, 200, 200));

    DrawString(650, 600, "SPACE : 決定", GetColor(200, 200, 200));
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