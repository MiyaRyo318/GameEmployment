#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet()
{
    m_Position = VGet(
        0.0f,
        0.0f,
        0.0f);

    m_Velocity = VGet(
        0.0f,
        0.0f,
        0.0f);

    m_Radius = 10.0f;

    m_Dead = true;
}

void Bullet::Create(
    VECTOR position,
    VECTOR velocity)
{
    m_Position = position;
    m_Velocity = velocity;

    m_Radius = 10.0f;

    m_Dead = false;
}

void Bullet::Update()
{
    if (m_Dead)
    {
        return;
    }

    // ’e‚ğˆÚ“®
    m_Position.x += m_Velocity.x;
    m_Position.y += m_Velocity.y;
    m_Position.z += m_Velocity.z;

    // “G‘¤‚Ü‚Å”ò‚ñ‚¾‚çíœ
    if (m_Position.z > 1000.0f)
    {
        m_Dead = true;
    }

    // ƒvƒŒƒCƒ„[‘¤‚Ü‚Å”ò‚ñ‚¾‚çíœ
    if (m_Position.z < -1000.0f)
    {
        m_Dead = true;
    }
}

void Bullet::Draw()
{
    if (m_Dead)
    {
        return;
    }

    DrawSphere3D(
        m_Position,
        m_Radius,
        16,
        GetColor(255, 255, 0),
        GetColor(255, 255, 0),
        TRUE);
}

bool Bullet::IsDead() const
{
    return m_Dead;
}