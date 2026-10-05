#include "TitleScene.h"
#include "DxLib.h"

void TitleScene::Init()
{
    m_IsStart = false;
    m_IsExitGame = false;

    m_TitleImage = LoadGraph("Data/Image/Title.png");

    m_MenuState = MenuState::MENU;

    // 最初はゲームスタートを選択
    m_MenuSelect = MenuSelect::GAME_START;

    m_IsUpKey = CheckHitKey(KEY_INPUT_UP);
    m_IsDownKey = CheckHitKey(KEY_INPUT_DOWN);
    m_IsSpaceKey = CheckHitKey(KEY_INPUT_SPACE);
    m_IsEscKey = CheckHitKey(KEY_INPUT_Z);
}

void TitleScene::Update()
{
    // 操作説明画面
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

    bool upKey = CheckHitKey(KEY_INPUT_UP);
    bool downKey = CheckHitKey(KEY_INPUT_DOWN);
    bool spaceKey = CheckHitKey(KEY_INPUT_SPACE);

    // 上キー
    if (upKey && !m_IsUpKey)
    {
        if (m_MenuSelect == MenuSelect::GAME_START)
        {
            // ゲームスタート → ゲームを終了する
            m_MenuSelect = MenuSelect::EXIT_GAME;
        }
        else if (m_MenuSelect == MenuSelect::OPERATION)
        {
            // 操作説明 → ゲームスタート
            m_MenuSelect = MenuSelect::GAME_START;
        }
        else if (m_MenuSelect == MenuSelect::EXIT_GAME)
        {
            // ゲームを終了する → 操作説明
            m_MenuSelect = MenuSelect::OPERATION;
        }
    }

    // 下キー
    if (downKey && !m_IsDownKey)
    {
        if (m_MenuSelect == MenuSelect::GAME_START)
        {
            // ゲームスタート → 操作説明
            m_MenuSelect = MenuSelect::OPERATION;
        }
        else if (m_MenuSelect == MenuSelect::OPERATION)
        {
            // 操作説明 → ゲームを終了する
            m_MenuSelect = MenuSelect::EXIT_GAME;
        }
        else if (m_MenuSelect == MenuSelect::EXIT_GAME)
        {
            // ゲームを終了する → ゲームスタート
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
        else if (m_MenuSelect == MenuSelect::EXIT_GAME)
        {
            m_IsExitGame = true;
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

    // 操作説明画面
    if (m_MenuState == MenuState::OPERATION)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);

        DrawBox(0,0,1600,900,GetColor(0, 0, 0),TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        DrawString(480,100,"操作説明",GetColor(255, 255, 255));

        DrawString(400,220,"Fキー      ：ドン",GetColor(255, 255, 255));

        DrawString(400,280,"Jキー      ：カッ",GetColor(255, 255, 255));

        DrawString(400,440,"Zキー       ：戻る",GetColor(255, 255, 255));

        return;
    }

    int white = GetColor(255, 255, 255);
    int yellow = GetColor(255, 255, 0);

    int gameStartColor = white;
    int operationColor = white;
    int exitGameColor = white;

    // 選択中の項目を黄色にする
    if (m_MenuSelect == MenuSelect::GAME_START)
    {
        gameStartColor = yellow;
    }
    else if (m_MenuSelect == MenuSelect::OPERATION)
    {
        operationColor = yellow;
    }
    else if (m_MenuSelect == MenuSelect::EXIT_GAME)
    {
        exitGameColor = yellow;
    }

    // メニュー
    DrawString(520,480,"ゲームスタート",gameStartColor);

    DrawString(520,530,"操作説明",operationColor);

    DrawString(520,580,"ゲームを終了する",exitGameColor);

    DrawString(470,650,"↑ / ↓：選択    SPACE：決定",white);
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

bool TitleScene::IsExitGame() const
{
    return m_IsExitGame;
}