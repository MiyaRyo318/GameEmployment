#include "Player.h"
#include "DxLib.h"

Player::Player()
{
    m_Position = VGet(
        0.0f,
        30.0f,
        -100.0f);

    m_Lane = 0;

    m_MaxHP = 100;
    m_HP = m_MaxHP;
}

void Player::Init()
{
    m_Position = VGet(
        0.0f,
        30.0f,
        -100.0f);

    m_Lane = 0;

    m_MaxHP = 100;
    m_HP = m_MaxHP;
}

void Player::Update()
{
    bool left = CheckHitKey(KEY_INPUT_LEFT);
    bool right = CheckHitKey(KEY_INPUT_RIGHT);

    // LEFTを押した瞬間
    if (left && !m_OldLeft)
    {
        if (m_Lane > -1)
        {
            m_Lane--;
        }
    }

    // RIGHTを押した瞬間
    if (right && !m_OldRight)
    {
        if (m_Lane < 1)
        {
            m_Lane++;
        }
    }

    // レーンに応じて位置を変更
    if (m_Lane == -1)
    {
        m_Position.x = -100.0f;
    }
    else if (m_Lane == 0)
    {
        m_Position.x = 0.0f;
    }
    else if (m_Lane == 1)
    {
        m_Position.x = 100.0f;
    }

    // 今のキー状態を保存
    m_OldLeft = left;
    m_OldRight = right;
}

void Player::Draw()
{
    // 赤い球
    DrawSphere3D(
        m_Position,
        30.0f,
        32,
        GetColor(255, 80, 80),
        GetColor(255, 80, 80),
        TRUE);

    // 画面座標へ変換
    VECTOR screenPos =
        ConvWorldPosToScreenPos(m_Position);

    // 周囲の円
    DrawCircle(
        (int)screenPos.x,
        (int)screenPos.y,
        40,
        GetColor(255, 150, 150),
        FALSE);
}

void Player::End()
{
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