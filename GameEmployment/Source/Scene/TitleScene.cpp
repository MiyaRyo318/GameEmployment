#include "TitleScene.h"
#include "DxLib.h"

void TitleScene::Init()
{
    m_IsStart = false;

    m_TitleImage = LoadGraph("Data/Image/Title.png");
}

void TitleScene::Update()
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        m_IsStart = true;
    }
}

void TitleScene::Draw()
{
    DrawGraph(0, 0, m_TitleImage, TRUE);

    DrawString(
        470,
        620,
        "PRESS SPACE KEY",
        GetColor(255, 255, 255));
}

void TitleScene::End()
{
    DeleteGraph(m_TitleImage);
}

bool TitleScene::IsStart() const
{
    return m_IsStart;
}