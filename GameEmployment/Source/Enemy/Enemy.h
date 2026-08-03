#pragma once

class Enemy
{
public:

    Enemy();

    void Init();

    void Update();

    void Draw();

    void StartAttack();

    int GetAttackLane() const;

private:

    int m_AttackLane;

    int m_AttackTimer;
};