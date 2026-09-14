#include "TitleScene.h"
#include "DxLib.h"

void TitleScene::Init()
{
    m_IsStart = false;

    m_TitleImage = LoadGraph("Data/Image/Title.png");

    m_MenuState = MenuState::MENU;

    m_MenuSelect = MenuSelect::GAME_START;

    m_IsUpKey = false;
    m_IsDownKey = false;
    m_IsSpaceKey = false;
    m_IsEscKey = false;
}

void TitleScene::Update()
{
    // =====================================
    // 操作説明画面
    // =====================================
    if (m_MenuState == MenuState::OPERATION)
    {
        bool zKey = CheckHitKey(KEY_INPUT_Z);

        // Zキーを押した瞬間だけ反応
        if (zKey && !m_IsEscKey)
        {
            m_MenuState = MenuState::MENU;
        }

        m_IsEscKey = zKey;

        return;
    }

    // =====================================
    // タイトルメニュー画面
    // =====================================

    bool upKey = CheckHitKey(KEY_INPUT_UP);
    bool downKey = CheckHitKey(KEY_INPUT_DOWN);
    bool spaceKey = CheckHitKey(KEY_INPUT_SPACE);

    // 上キー
    if (upKey && !m_IsUpKey)
    {
        if (m_MenuSelect == MenuSelect::GAME_START)
        {
            m_MenuSelect = MenuSelect::OPERATION;
        }
        else
        {
            m_MenuSelect = MenuSelect::GAME_START;
        }
    }

    // 下キー
    if (downKey && !m_IsDownKey)
    {
        if (m_MenuSelect == MenuSelect::GAME_START)
        {
            m_MenuSelect = MenuSelect::OPERATION;
        }
        else
        {
            m_MenuSelect = MenuSelect::GAME_START;
        }
    }

    // SPACEキー
    if (spaceKey && !m_IsSpaceKey)
    {
        if (m_MenuSelect == MenuSelect::GAME_START)
        {
            m_IsStart = true;
        }
        else if (m_MenuSelect == MenuSelect::OPERATION)
        {
            m_MenuState = MenuState::OPERATION;
        }
    }

    // 前回のキー状態を保存
    m_IsUpKey = upKey;
    m_IsDownKey = downKey;
    m_IsSpaceKey = spaceKey;
}

void TitleScene::Draw()
{
    // タイトル画像
    DrawGraph(0, 0, m_TitleImage, TRUE);

    // =====================================
    // 操作説明画面
    // =====================================
    if (m_MenuState == MenuState::OPERATION)
    {
        // 黒い半透明風の背景
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
        DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        DrawString(480, 100, "操作説明", GetColor(255, 255, 255));

        DrawString(400, 220, "Fキー      ：ドン", GetColor(255, 255, 255));

        DrawString(400, 280, "Jキー      ：カッ", GetColor(255, 255, 255));

        DrawString(400, 340, "← / →     ：プレイヤー移動",
            GetColor(255, 255, 255));

        DrawString(400, 440, "Zキー       ：戻る",
            GetColor(255, 255, 255));

        return;
    }

    // =====================================
    // タイトルメニュー画面
    // =====================================

    int white = GetColor(255, 255, 255);
    int yellow = GetColor(255, 255, 0);

    int gameStartColor = white;
    int operationColor = white;

    if (m_MenuSelect == MenuSelect::GAME_START)
    {
        gameStartColor = yellow;
    }
    else if (m_MenuSelect == MenuSelect::OPERATION)
    {
        operationColor = yellow;
    }

    DrawString(520, 500, "ゲームスタート", gameStartColor);

    DrawString(520, 550, "操作説明", operationColor);

    DrawString(470, 630, "↑ / ↓：選択    SPACE：決定",
        white);
}

void TitleScene::End()
{
    if (m_TitleImage != -1)
    {
        DeleteGraph(m_TitleImage);

        m_TitleImage = -1;
    }
}

bool TitleScene::IsStart() const
{
    return m_IsStart;
}