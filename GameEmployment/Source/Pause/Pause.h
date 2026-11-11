#pragma once
#include "DxLib.h"
#include "../Input/InputManager.h"

enum class PauseResult
{
    None,
    Resume,
    Retry,
    ReturnTitle
};

class Pause
{
public:
    Pause();

    void Init();

    // ポーズ開始
    void Start();

    // ポーズ中の操作
    PauseResult Update(InputManager& input);

    // ポーズ画面の描画
    void Draw();

    bool IsPaused() const;

private:
    bool m_IsPaused;
    int m_PauseSelect;
};
