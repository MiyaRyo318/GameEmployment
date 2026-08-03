#include "Enemy.h"
#include "DxLib.h"
#include <cstdlib>

Enemy::Enemy()
{
    m_AttackLane = 0;
    m_AttackTimer = 0;
}

void Enemy::Init()
{
    m_AttackTimer = 180;
}

void Enemy::Update()
{
    m_AttackTimer--;

    if (m_AttackTimer <= 0)
    {
        StartAttack();

        m_AttackTimer = 180;
    }
}

void Enemy::StartAttack()
{
    m_AttackLane = rand() % 3 - 1;
}

void Enemy::Draw()
{
    DrawSphere3D(
        VGet(0, 0, 20),
        2.0f,
        16,
        GetColor(255, 0, 0),
        GetColor(255, 0, 0),
        TRUE);

    DrawFormatString(
        20,
        120,
        GetColor(255, 255, 255),
        "Attack Lane : %d",
        m_AttackLane);
}

int Enemy::GetAttackLane() const
{
    return m_AttackLane;
}