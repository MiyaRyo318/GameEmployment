#include "GameClear.h"
#include "DxLib.h"

GameClear::GameClear()
{
    m_ReturnTitle = false;
}

void GameClear::Init()
{
    m_ReturnTitle = false;
}

void GameClear::Update()
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        m_ReturnTitle = true;
    }
}

void GameClear::Draw()
{
    // 背景
    DrawBox(
        0,
        0,
        1600,
        900,
        GetColor(0, 0, 0),
        TRUE
    );

    // ゲームクリア
    DrawString(
        650,
        350,
        "GAME CLEAR!",
        GetColor(255, 255, 255)
    );

    // タイトルに戻る
    DrawString(
        650,
        450,
        "タイトルに戻る",
        GetColor(255, 255, 255)
    );

    // 操作説明
    DrawString(
        650,
        500,
        "Enter : タイトルに戻る",
        GetColor(200, 200, 200)
    );
}

void GameClear::End()
{
}

bool GameClear::IsReturnTitle() const
{
    return m_ReturnTitle;
}