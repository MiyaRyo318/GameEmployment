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

    m_Owner = BULLET_PLAYER;
}

void Bullet::Create(
    VECTOR position,
    VECTOR velocity,
    BulletOwner owner)
{
    m_Position = position;

    m_Velocity = velocity;

    m_Radius = 10.0f;

    m_Dead = false;

    m_Owner = owner;
}

void Bullet::Update()
{
    if (m_Dead)
    {
        return;
    }

    m_Position.x += m_Velocity.x;
    m_Position.y += m_Velocity.y;
    m_Position.z += m_Velocity.z;

    // ”ÍˆÍŠO‚Éo‚½‚çíœ
    if (m_Position.z > 1000.0f ||
        m_Position.z < -1000.0f)
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

    if (m_Owner == BULLET_PLAYER)
    {
        // ƒvƒŒƒCƒ„[‚Ì’e
        DrawSphere3D(
            m_Position,
            m_Radius,
            16,
            GetColor(255, 255, 0),
            GetColor(255, 255, 0),
            TRUE);
    }
    else
    {
        // “G‚Ì’e
        DrawSphere3D(
            m_Position,
            m_Radius,
            16,
            GetColor(255, 0, 0),
            GetColor(255, 0, 0),
            TRUE);
    }
}

bool Bullet::IsDead() const
{
    return m_Dead;
}

VECTOR Bullet::GetPosition() const
{
    return m_Position;
}

void Bullet::Destroy()
{
    m_Dead = true;
}

BulletOwner Bullet::GetOwner() const
{
    return m_Owner;
}