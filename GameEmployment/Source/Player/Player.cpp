#include "Player.h"

Player::Player()
{
    m_Lane = 0;
}

void Player::Init()
{
    m_MaxHP = 100;
    m_HP = 100;

    m_Lane = 0;

    m_X = 0.0f;
    m_Y = 0.0f;
    m_Z = 0.0f;
}

void Player::Update()
{
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        if (m_Lane > -1)
        {
            m_Lane--;
        }
    }

    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        if (m_Lane < 1)
        {
            m_Lane++;
        }
    }

    m_X = m_Lane * 5.0f;
}

void Player::Draw()
{
    DrawSphere3D(
        VGet(m_X, 0, 0),
        1.0f,
        16,
        GetColor(0, 255, 0),
        GetColor(0, 255, 0),
        TRUE);
}

int Player::GetLane() const
{
    return m_Lane;
}

void Player::Damage(int damage)
{
    m_HP -= damage;

    if (m_HP < 0)
    {
        m_HP = 0;
    }
}

int Player::GetHP() const
{
    return m_HP;
}

bool Player::IsDead() const
{
    return m_HP <= 0;
}