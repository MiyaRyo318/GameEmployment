#include "GameOver.h"
#include "DxLib.h"

GameOver::GameOver()
{
    m_ReturnTitle = false;
}

void GameOver::Init()
{
    m_ReturnTitle = false;
}

void GameOver::Update()
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        m_ReturnTitle = true;
    }
}

void GameOver::Draw()
{
    // 画面を黒くする
    DrawBox(
        0,
        0,
        1600,
        900,
        GetColor(0, 0, 0),
        TRUE);

    // GAME OVER
    DrawString(
        650,
        350,
        "GAME OVER",
        GetColor(255, 0, 0));

    // タイトルに戻る
    DrawString(
        650,
        450,
        "タイトルに戻る",
        GetColor(255, 255, 255));

    DrawString(
        650,
        500,
        "Enter : タイトルに戻る",
        GetColor(200, 200, 200));
}

void GameOver::End()
{
}

bool GameOver::IsReturnTitle() const
{
    return m_ReturnTitle;
}