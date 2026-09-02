#include "Player.h"
#include "DxLib.h"

Player::Player()
{
    m_Model = -1;

    m_Position = VGet(
        0.0f,
        30.0f,
        -100.0f);

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

    // プレイヤー位置
    m_Position = VGet(
        0.0f,
        60.0f,
        -200.0f);

    m_Rotation = VGet(
        0.0f,
        DX_PI_F / 2.0f,
        0.0f);

    // とりあえず大きくする
    m_Scale = VGet(
        10.0f,
        10.0f,
        10.0f);

    MV1SetPosition(
        m_Model,
        m_Position);

    MV1SetRotationXYZ(
        m_Model,
        m_Rotation);

    MV1SetScale(
        m_Model,
        m_Scale);

    m_Lane = 0;

    m_HP = m_MaxHP;

    m_OldLeft = false;
    m_OldRight = false;
}

void Player::Update()
{
    bool left =
        CheckHitKey(KEY_INPUT_LEFT);

    bool right =
        CheckHitKey(KEY_INPUT_RIGHT);

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

    // レーンに応じてX座標を変更
    if (m_Lane == -1)
    {
        m_Position.x = -70.0f;
    }
    else if (m_Lane == 0)
    {
        m_Position.x = 0.0f;
    }
    else if (m_Lane == 1)
    {
        m_Position.x = 70.0f;
    }

    // モデルの位置を更新
    if (m_Model != -1)
    {
        MV1SetPosition(
            m_Model,
            m_Position);
    }

    // 現在のキー状態を保存
    m_OldLeft = left;
    m_OldRight = right;
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