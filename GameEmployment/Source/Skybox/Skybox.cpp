#include "Skybox.h"
#include "DxLib.h"

Skybox::Skybox()
{
    m_Model = -1;

    m_Position = VGet(
        0.0f,
        0.0f,
        0.0f);

    m_Rotation = VGet(
        0.0f,
        0.0f,
        0.0f);

    m_Scale = VGet(
        20.0f,
        20.0f,
        20.0f);

    // 背景のスクロール速度
    m_ScrollSpeed = 0.5f;
}

void Skybox::Init()
{
    m_Model = MV1LoadModel(
        "Data/Skybox/Skybox.x");

    if (m_Model == -1)
    {
        MessageBox(
            nullptr,
            "Skybox.x の読み込みに失敗しました",
            "Skybox Error",
            MB_OK);

        return;
    }

    MV1SetPosition(
        m_Model,
        m_Position);

    MV1SetRotationXYZ(
        m_Model,
        m_Rotation);

    MV1SetScale(
        m_Model,
        m_Scale);
}

void Skybox::Update()
{
    if (m_Model == -1)
    {
        return;
    }

    // 背景を左方向へ移動
    m_Position.x -= m_ScrollSpeed;

    // 一定距離まで移動したら右側へ戻す
    if (m_Position.x < -1000.0f)
    {
        m_Position.x = 1000.0f;
    }

    // モデルの位置を更新
    MV1SetPosition(
        m_Model,
        m_Position);
}

void Skybox::Draw()
{
    if (m_Model != -1)
    {
        MV1DrawModel(m_Model);
    }
}

void Skybox::End()
{
    if (m_Model != -1)
    {
        MV1DeleteModel(m_Model);
        m_Model = -1;
    }
}