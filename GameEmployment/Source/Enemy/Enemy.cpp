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

    m_MoveLane = 0;
    m_MoveTimer = 180;
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

    // HP初期化
    m_MaxHP = 100;
    m_HP = m_MaxHP;

    m_MoveLane = 0;
    m_MoveTimer = 180;
}

void Enemy::Update()
{
    // 移動タイマー
    m_MoveTimer--;

    if (m_MoveTimer <= 0)
    {
        // -1 = 左
        //  0 = 中央
        //  1 = 右
        m_MoveLane = rand() % 3 - 1;

        // レーン位置
        if (m_MoveLane == -1)
        {
            m_Position.x = -100.0f;
        }
        else if (m_MoveLane == 0)
        {
            m_Position.x = 0.0f;
        }
        else if (m_MoveLane == 1)
        {
            m_Position.x = 100.0f;
        }

        // モデルの位置を更新
        MV1SetPosition(
            m_Model,
            m_Position);

        // 次の移動まで3秒
        m_MoveTimer = 180;
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