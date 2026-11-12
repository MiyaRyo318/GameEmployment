#include "Pause.h"

Pause::Pause()
{
    m_IsPaused = false;
    m_PauseSelect = 0;
}

void Pause::Init()
{
    m_IsPaused = false;
    m_PauseSelect = 0;
}

void Pause::Start()
{
    m_IsPaused = true;

    // 初期選択は「再開」
    m_PauseSelect = 0;
}

PauseResult Pause::Update(InputManager& input)
{
    if (!m_IsPaused)
    {
        return PauseResult::None;
    }

    // ESCで再開
    if (input.IsPauseTrigger())
    {
        m_IsPaused = false;
        return PauseResult::Resume;
    }

    // 上
    if (input.IsUpTrigger())
    {
        m_PauseSelect--;

        if (m_PauseSelect < 0)
        {
            m_PauseSelect = 2;
        }
    }

    // 下
    if (input.IsDownTrigger())
    {
        m_PauseSelect++;

        if (m_PauseSelect > 2)
        {
            m_PauseSelect = 0;
        }
    }

    // 決定
    if (input.IsEnterTrigger())
    {
        if (m_PauseSelect == 0)
        {
            m_IsPaused = false;
            return PauseResult::Resume;
        }
        else if (m_PauseSelect == 1)
        {
            return PauseResult::Retry;
        }
        else if (m_PauseSelect == 2)
        {
            return PauseResult::ReturnTitle;
        }
    }

    return PauseResult::None;
}

void Pause::Draw()
{
    if (!m_IsPaused)
    {
        return;
    }

    // 画面を暗くする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);

    DrawBox(0, 0, 1600, 900,GetColor(0, 0, 0),TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    int white = GetColor(255, 255, 255);
    int yellow = GetColor(255, 255, 0);

    // PAUSE
    DrawString(760, 180, "PAUSE", white);

    // メニューの色
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

    // メニュー
    DrawString(700, 350, "再開", resumeColor);
    DrawString(700, 420, "リトライ", retryColor);
    DrawString(700, 490, "タイトルに戻る", titleColor);
    DrawFormatString(580, 780,white,"↑ / ↓：選択    SPACE：決定    ESC：再開");
}

bool Pause::IsPaused() const
{
    return m_IsPaused;
}
