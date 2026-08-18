#pragma once

#include "DxLib.h"

class Enemy
{
public:

    Enemy();

    void Init();

    void Load();

    void Update();

    void Draw();

    void End();

    void StartAttack();

    int GetAttackLane() const;

private:

    // 3Dƒ‚ƒfƒ‹
    int m_Model;

    // “G‚ÌˆÊ’u
    VECTOR m_Position;

    // “G‚Ì‰ñ“]
    VECTOR m_Rotation;

    // “G‚Ì‘å‚«‚³
    VECTOR m_Scale;

    // UŒ‚ƒŒ[ƒ“
    int m_AttackLane;

    // UŒ‚ƒ^ƒCƒ}[
    int m_AttackTimer;
};