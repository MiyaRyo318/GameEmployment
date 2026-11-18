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
#include "../Pause/Pause.h"

class GameScene
{
public:

    GameScene();
    ~GameScene();

    void Init(int difficulty);

    void Update();

    void Draw();

    void End();

    bool IsGameClear() const;

    bool IsGameOver() const;

    bool IsBranchRequested() const;

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

    int m_Difficulty;

    JudgeType m_LastJudge = NONE;

    Pause m_Pause;

    bool m_IsRetry;
    bool m_IsReturnTitle;
    bool m_BGMStarted;
    bool m_IsBranchRequested;

    // ゲーム開始前の待機
    bool m_IsWaitingStart;
    int m_WaitStartTime;

    // 分岐画面
    bool m_IsBranchSelecting;

    // 分岐ルート
    int m_SelectedBranch;

    // 分岐後の再開カウントダウン
    bool m_IsBranchCountdown;
    int m_BranchCountdownStart;

    // 分岐画面に入った時刻
    int m_BranchPauseStart;
};