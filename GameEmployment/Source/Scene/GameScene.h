#pragma once

#include "DxLib.h"
#include "../Camera/Camera.h"
#include "../Note/NoteManager.h"
#include "../Input/InputManager.h"
#include "../Judge/JudgeManager.h"

class GameScene
{
public:

    GameScene();
    ~GameScene();

    // 初期化
    void Init();

    // 更新
    void Update();

    // 描画
    void Draw();

    // 終了
    void End();

private:

    Camera m_Camera;

    //Player m_Player;

    //Enemy m_Monster;

    NoteManager m_NoteManager;

    InputManager m_Input;

    JudgeManager m_Judge;

    // ゲーム開始時間
    int m_StartTime;

    // 現在の経過時間(秒)
    float m_CurrentTime;

    JudgeType m_LastJudge = NONE;
};