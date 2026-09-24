#pragma once

#include "DxLib.h"

class Player
{
public:
    Player();

    void Init();
    void Update();
    void Draw();
    void End();

    void Damage(int damage);

    int GetHP() const;
    bool IsDead() const;

    VECTOR GetPosition() const;
    float GetCollisionRadius() const;

    void AutoMove(float deltaTime);

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

    float m_AutoMoveTime;
};