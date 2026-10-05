#pragma once

#include "DxLib.h"
#include "../Camera/Camera.h"
#include "../Note/NoteManager.h"
#include "../Input/InputManager.h"
#include "../Judge/JudgeManager.h"
#include "../Sound/Sound.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Bullet/BulletManager.h"

class GameScene
{
public:

    GameScene();
    ~GameScene();

    void Init();

    void Update();

    void Draw();

    void End();

    bool IsGameClear() const;

    bool IsGameOver() const;

    // ポーズ結果
    bool IsRetry() const;
    bool IsReturnTitle() const;

private:

    Camera m_Camera;

    NoteManager m_NoteManager;

    InputManager m_Input;

    JudgeManager m_Judge;

    Sound m_Sound;

    Player m_Player;

    Enemy m_Enemy;

    BulletManager m_BulletManager;

    int m_StartTime;

    float m_CurrentTime;

    float m_AutoMoveTime;

    JudgeType m_LastJudge = NONE;

    // ポーズ
    
    bool m_IsPaused;

    // 0 = 再開
    // 1 = リトライ
    // 2 = タイトルに戻る
    int m_PauseSelect;

    bool m_IsRetry;
    bool m_IsReturnTitle;
    bool m_BGMStarted;
};