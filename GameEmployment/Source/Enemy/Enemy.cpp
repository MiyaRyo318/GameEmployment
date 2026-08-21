#include "Enemy.h"
#include "DxLib.h"
#include <cstdlib>

Enemy::Enemy()
{
    m_Model = -1;

    m_Position = VGet(0.0f, 0.0f, 10.0f);

    m_Rotation = VGet(
        0.0f,
        DX_PI_F / 2.0f,
        0.0f);

    m_Scale = VGet(30.0f, 30.0f, 30.0f);

    m_AttackLane = 0;
    m_AttackTimer = 0;

    m_MaxHP = 100;
    m_HP = m_MaxHP;
}

void Enemy::Init()
{
    m_Model = MV1LoadModel("Data/Enemy/Enemy.x");

    if (m_Model == -1)
    {
        MessageBox(
            nullptr,
            "Enemy.x ÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩ",
            "Enemy Error",
            MB_OK);

        return;
    }

    m_Position = VGet(0.0f, 80.0f, 20.0f);

    m_Rotation = VGet(
        0.0f,
        DX_PI_F / 2.0f,
        0.0f);

    m_Scale = VGet(
        30.0f,
        30.0f,
        30.0f);

    MV1SetPosition(
        m_Model,
        m_Position);

    MV1SetRotationXYZ(
        m_Model,
        m_Rotation);

    MV1SetScale(
        m_Model,
        m_Scale);

    m_AttackTimer = 180;

    // HPèâä˙âª
    m_MaxHP = 100;
    m_HP = m_MaxHP;
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
    // -1 = ç∂
    //  0 = íÜâõ
    //  1 = âE
    m_AttackLane = rand() % 3 - 1;
}

void Enemy::Draw()
{

    // EnemyÉÇÉfÉã
    if (m_Model != -1)
    {
        MV1DrawModel(m_Model);
    }

    DrawFormatString(
        20,
        120,
        GetColor(255, 255, 255),
        "ENEMY DRAW OK");
}

void Enemy::End()
{
    if (m_Model != -1)
    {
        MV1DeleteModel(m_Model);

        m_Model = -1;
    }
}

int Enemy::GetAttackLane() const
{
    return m_AttackLane;
}

void Enemy::Damage(int damage)
{
    m_HP -= damage;

    if (m_HP < 0)
    {
        m_HP = 0;
    }
}

int Enemy::GetHP() const
{
    return m_HP;
}

bool Enemy::IsDead() const
{
    return m_HP <= 0;
}