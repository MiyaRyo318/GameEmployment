#include "TitleScene.h"
#include "DxLib.h"

void TitleScene::Init()
{
    m_IsStart = false;
    m_IsExitGame = false;

    if (m_TitleImage == -1)
    {
        m_TitleImage = LoadGraph("Data/Image/Title.png");
    }

    m_MenuState = MenuState::MENU;
    m_MenuSelect = MenuSelect::GAME_START;

    m_DifficultySelect = 1;
    m_ShowUnavailable = false;

    // 初期化直後に押しっぱなしのキーを誤認しない
    m_IsUpKey = CheckHitKey(KEY_INPUT_UP) != 0;
    m_IsDownKey = CheckHitKey(KEY_INPUT_DOWN) != 0;
    m_IsSpaceKey = CheckHitKey(KEY_INPUT_SPACE) != 0;
    m_IsZKey = CheckHitKey(KEY_INPUT_Z) != 0;
}

void TitleScene::Update()
{
    bool upKey = CheckHitKey(KEY_INPUT_UP) != 0;
    bool downKey = CheckHitKey(KEY_INPUT_DOWN) != 0;
    bool spaceKey = CheckHitKey(KEY_INPUT_SPACE) != 0;
    bool zKey = CheckHitKey(KEY_INPUT_Z) != 0;

    bool upPressed = upKey && !m_IsUpKey;
    bool downPressed = downKey && !m_IsDownKey;
    bool spacePressed = spaceKey && !m_IsSpaceKey;
    bool zPressed = zKey && !m_IsZKey;

    // 操作説明画面
    if (m_MenuState == MenuState::OPERATION)
    {
        if (zPressed)
        {
            m_MenuState = MenuState::MENU;
        }
    }
    // 難易度選択画面
    else if (m_MenuState == MenuState::DIFFICULTY)
    {
        if (upPressed)
        {
            m_DifficultySelect--;

            if (m_DifficultySelect < 0)
            {
                m_DifficultySelect = 2;
            }

            m_ShowUnavailable = false;
        }

        if (downPressed)
        {
            m_DifficultySelect++;

            if (m_DifficultySelect > 2)
            {
                m_DifficultySelect = 0;
            }

            m_ShowUnavailable = false;
        }

        // Zキーでタイトルメニューに戻る
        if (zPressed)
        {
            m_MenuState = MenuState::MENU;
            m_ShowUnavailable = false;
        }

        // SPACEキーで難易度を決定
        if (spacePressed)
        {
            // 選択した難易度でゲームを開始
            m_IsStart = true;
            m_ShowUnavailable = false;
        }
    }
    // タイトルメニュー
    else
    {
        if (upPressed)
        {
            if (m_MenuSelect == MenuSelect::GAME_START)
            {
                m_MenuSelect = MenuSelect::EXIT_GAME;
            }
            else if (m_MenuSelect == MenuSelect::OPERATION)
            {
                m_MenuSelect = MenuSelect::GAME_START;
            }
            else
            {
                m_MenuSelect = MenuSelect::OPERATION;
            }
        }

        if (downPressed)
        {
            if (m_MenuSelect == MenuSelect::GAME_START)
            {
                m_MenuSelect = MenuSelect::OPERATION;
            }
            else if (m_MenuSelect == MenuSelect::OPERATION)
            {
                m_MenuSelect = MenuSelect::EXIT_GAME;
            }
            else
            {
                m_MenuSelect = MenuSelect::GAME_START;
            }
        }

        if (spacePressed)
        {
            if (m_MenuSelect == MenuSelect::GAME_START)
            {
                // 直接ゲームを開始せず難易度選択へ
                m_MenuState = MenuState::DIFFICULTY;
                m_DifficultySelect = 1;
                m_ShowUnavailable = false;
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
    }

    // 前回のキー状態を保存
    m_IsUpKey = upKey;
    m_IsDownKey = downKey;
    m_IsSpaceKey = spaceKey;
    m_IsZKey = zKey;
}

void TitleScene::Draw()
{
    // タイトル画像
    if (m_TitleImage != -1)
    {
        DrawGraph(0, 0, m_TitleImage, TRUE);
    }

    int white = GetColor(255, 255, 255);
    int yellow = GetColor(255, 255, 0);
    int gray = GetColor(180, 180, 180);

    // 操作説明画面
    if (m_MenuState == MenuState::OPERATION)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
        DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        DrawString(480, 100, "操作説明", white);
        DrawString(400, 220, "Fキー ：ドン", white);
        DrawString(400, 280, "Jキー ：カッ", white);
        DrawString(400, 440, "Zキー ：戻る", white);

        return;
    }

    // 難易度選択画面
    if (m_MenuState == MenuState::DIFFICULTY)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
        DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        DrawString(600, 250, "難易度選択", white);

        // 簡単
        DrawString(620, 350,m_DifficultySelect == 0 ? "> 簡単" : "  簡単",m_DifficultySelect == 0 ? yellow : gray);

        // 普通
        DrawString(620, 410,m_DifficultySelect == 1 ? "> 普通" : "  普通",m_DifficultySelect == 1 ? yellow : white);

        // 難しい
        DrawString(620, 470,m_DifficultySelect == 2 ? "> 難しい" : "  難しい",m_DifficultySelect == 2 ? yellow : gray);

        DrawString(550, 570,"↑ / ↓：選択    SPACE：決定", white);

        DrawString(550, 610,"Z：タイトルに戻る", white);

        if (m_ShowUnavailable)
        {
            DrawString(550, 680,"この難易度は現在プレイできません。",GetColor(255, 100, 100));
        }

        return;
    }

    // タイトルメニュー
    int gameStartColor = white;
    int operationColor = white;
    int exitGameColor = white;

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

    DrawString(520, 480, "ゲームスタート", gameStartColor);
    DrawString(520, 530, "操作説明", operationColor);
    DrawString(520, 580, "ゲームを終了する", exitGameColor);
    DrawString(470, 650,"↑ / ↓：選択    SPACE：決定", white);
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

int TitleScene::GetDifficultySelect() const
{
    return m_DifficultySelect;
}