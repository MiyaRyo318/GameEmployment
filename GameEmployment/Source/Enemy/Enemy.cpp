#include "Enemy.h"
#include "DxLib.h"
#include <cstdlib>

Enemy::Enemy()
{
    m_Model = -1;

    m_Position = VGet(
        200.0f,
        80.0f,
        0.0f);

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

    // 当たり判定の大きさ
    m_CollisionRadius = 50.0f;

    m_ShootTimer = 120;
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

    // 敵を画面右側に配置
    m_Position = VGet(
        120.0f,
        80.0f,
        0.0f);

    m_Rotation = VGet(
        0.0f,
        -53.5f,
        0.0f);

    m_Scale = VGet(
        30.0f,
        30.0f,
        30.0f);

    MV1SetPosition(m_Model, m_Position);
    MV1SetRotationXYZ(m_Model, m_Rotation);
    MV1SetScale(m_Model, m_Scale);

    m_AttackTimer = 180;
    m_MaxHP = 100;
    m_HP = m_MaxHP;
    m_MoveLane = 0;
    m_MoveTimer = 180;
    m_ShootTimer = 120;
}

void Enemy::Update()
{
    // 横スクロール中は通常のレーン移動を行わない
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

VECTOR Enemy::GetPosition() const
{
    return m_Position;
}

float Enemy::GetCollisionRadius() const
{
    return m_CollisionRadius;
}

bool Enemy::CanShoot()
{
    m_ShootTimer--;

    if (m_ShootTimer <= 0)
    {
        // ランダムなレーンを決める
        StartAttack();

        // 次の発射まで待つ
        m_ShootTimer = 120;

        return true;
    }

    return false;
}

void Enemy::AutoMove(float deltaTime)
{
    
}