#pragma once

#include "DxLib.h"

class Player
{
public:

    Player();

    void Init();

    void Update();

    // Ž©“®ˆÚ“®
    void AutoMove(float deltaTime);

    void Draw();

    void End();

    void Damage(int damage);

    int GetHP() const;

    bool IsDead() const;

    VECTOR GetPosition() const;

    float GetCollisionRadius() const;

private:

    int m_Model;

    VECTOR m_Position;

    VECTOR m_Rotation;

    VECTOR m_Scale;

    int m_Lane;

    int m_HP;
    int m_MaxHP;

    bool m_OldLeft;
    bool m_OldRight;

    // Ž©“®ˆÚ“®—p
    float m_AutoMoveTime;
};