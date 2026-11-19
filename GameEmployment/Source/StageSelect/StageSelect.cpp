#include "StageSelect.h"

StageSelect::StageSelect()
{
    m_SelectedStage = 0;
    m_IsSelected = false;
}

void StageSelect::Init()
{
    m_SelectedStage = 0;
    m_IsSelected = false;
}

void StageSelect::Update()
{
    // 左キーで前のステージ
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        m_SelectedStage--;

        if (m_SelectedStage < 0)
        {
            m_SelectedStage = 1;
        }
    }

    // 右キーで次のステージ
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        m_SelectedStage++;

        if (m_SelectedStage > 1)
        {
            m_SelectedStage = 0;
        }
    }

    // SPACEキーで決定
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        m_IsSelected = true;
    }
}

void StageSelect::Draw()
{
    // 背景
    DrawBox(0, 0, 1600, 900, GetColor(10, 15, 35), TRUE);

    DrawString(650, 200, "STAGE SELECT", GetColor(255, 255, 255));

    // ステージ1
    int color1 = (m_SelectedStage == 0)? GetColor(255, 255, 0): GetColor(180, 180, 180);

    DrawString(400, 400, "STAGE 2", color1);

    // ステージ2
    int color2 = (m_SelectedStage == 1)? GetColor(255, 255, 0): GetColor(180, 180, 180);

    DrawString(1000, 400, "STAGE 3", color2);

    DrawString(600, 650, "LEFT / RIGHT : SELECT", GetColor(255, 255, 255));

    DrawString(650, 700, "SPACE : DECIDE", GetColor(255, 255, 255));
}

bool StageSelect::IsSelected() const
{
    return m_IsSelected;
}

int StageSelect::GetSelectedStage() const
{
    return m_SelectedStage;
}