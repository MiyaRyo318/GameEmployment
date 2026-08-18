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
}

void Enemy::Init()
{
    m_Model = MV1LoadModel("Data/Enemy/Enemy.x");

    if (m_Model == -1)
    {
        MessageBox(
            nullptr,
            "Enemy.x の読み込みに失敗しました",
            "Enemy Error",
            MB_OK);

        return;
    }

    m_Position = VGet(0.0f, 80.0f, 20.0f);

    m_Rotation = VGet(0.0f, 0.0f, 0.0f);

    m_Scale = VGet(5.0f, 5.0f, 5.0f);

    MV1SetPosition(m_Model, m_Position);
    MV1SetRotationXYZ(m_Model, m_Rotation);
    MV1SetScale(m_Model, m_Scale);

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
    // -1 = 左
    //  0 = 中央
    //  1 = 右
    m_AttackLane = rand() % 3 - 1;
}

void Enemy::Draw()
{
    // デバッグ用の赤い球
    DrawSphere3D(
        VGet(0.0f, 80.0f, 20.0f),
        50.0f,
        32,
        GetColor(255, 0, 0),
        GetColor(255, 0, 0),
        TRUE);

    // Enemyモデル
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