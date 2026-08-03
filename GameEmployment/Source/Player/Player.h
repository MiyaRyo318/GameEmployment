#pragma once

#include "DxLib.h"

class Player
{
public:

    Player();

    void Init();

    void Update();

    void Draw();

    void Damage(int damage);

    int GetHP() const;

    bool IsDead() const;

    int GetLane() const;

private:

    int m_HP;
    int m_MaxHP;

    int m_Lane;

    float m_X;
    float m_Y;
    float m_Z;
};