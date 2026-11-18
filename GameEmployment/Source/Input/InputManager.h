#pragma once

class InputManager
{
public:

    void Update();

    bool IsDon() const;
    bool IsKa() const;

    bool IsDonTrigger() const;
    bool IsKaTrigger() const;

    // ポーズ
    bool IsPauseTrigger() const;

    // ポーズメニュー
    bool IsUpTrigger() const;
    bool IsDownTrigger() const;
    bool IsEnterTrigger() const;

    // 分岐選択
    bool IsLeftTrigger() const;
    bool IsRightTrigger() const;

    // SPACEキー
    bool IsSpaceTrigger() const;

private:

    bool m_Don = false;
    bool m_Ka = false;

    bool m_OldDon = false;
    bool m_OldKa = false;

    bool m_DonTrigger = false;
    bool m_KaTrigger = false;

    // ESC
    bool m_Pause = false;
    bool m_OldPause = false;
    bool m_PauseTrigger = false;

    // ↑
    bool m_Up = false;
    bool m_OldUp = false;
    bool m_UpTrigger = false;

    // ↓
    bool m_Down = false;
    bool m_OldDown = false;
    bool m_DownTrigger = false;

    // Enter
    bool m_Enter = false;
    bool m_OldEnter = false;
    bool m_EnterTrigger = false;

    // ←
    bool m_Left = false;
    bool m_OldLeft = false;
    bool m_LeftTrigger = false;

    // →
    bool m_Right = false;
    bool m_OldRight = false;
    bool m_RightTrigger = false;

    // SPACE
    bool m_Space = false;
    bool m_OldSpace = false;
    bool m_SpaceTrigger = false;
};