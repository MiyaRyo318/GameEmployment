#include "Player.h"
#include "DxLib.h"

Player::Player()
{
    m_Model = -1;

    m_Position = VGet(
        -100.0f,
        60.0f,
        0.0f);

    m_Rotation = VGet(
        0.0f,
        0.0f,
        0.0f);

    m_Scale = VGet(
        1.0f,
        1.0f,
        1.0f);

    m_Lane = 0;

    m_MaxHP = 100;
    m_HP = m_MaxHP;

    m_OldLeft = false;
    m_OldRight = false;

    m_AutoMoveTime = 0.0f;
}

void Player::Init()
{
    m_Model = MV1LoadModel(
        "Data/Player/Player.x");

    if (m_Model == -1)
    {
        MessageBox(
            nullptr,
            "Player.x の読み込みに失敗しました",
            "Player Error",
            MB_OK);

        return;
    }

    // プレイヤーを画面左側に配置
    m_Position = VGet(
        -120.0f,
        60.0f,
        0.0f);

    m_Rotation = VGet(
        0.0f,
        0.0f,
        0.0f);

    m_Scale = VGet(
        10.0f,
        10.0f,
        10.0f);

    MV1SetPosition(m_Model, m_Position);
    MV1SetRotationXYZ(m_Model, m_Rotation);
    MV1SetScale(m_Model, m_Scale);

    m_Lane = 0;
    m_HP = m_MaxHP;
    m_OldLeft = false;
    m_OldRight = false;
    m_AutoMoveTime = 0.0f;
}

void Player::Update()
{
    // 横スクロール中は手動移動を行わない
}

void Player::Draw()
{
    if (m_Model != -1)
    {
        MV1DrawModel(m_Model);

        DrawFormatString(
            20,
            150,
            GetColor(255, 255, 255),
            "PLAYER DRAW OK");
    }
    else
    {
        DrawFormatString(
            20,
            150,
            GetColor(255, 0, 0),
            "PLAYER MODEL ERROR");
    }
}

void Player::End()
{
    if (m_Model != -1)
    {
        MV1DeleteModel(m_Model);

        m_Model = -1;
    }
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

VECTOR Player::GetPosition() const
{
    return m_Position;
}

float Player::GetCollisionRadius() const
{
    return 40.0f;
}

void Player::AutoMove(float deltaTime)
{
    // プレイヤーは画面左側に固定する
    // 現在は自動移動させない
}