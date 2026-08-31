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
}

void Skybox::Init()
{
    m_Model = MV1LoadModel(
        "Data/Skybox/Skybox.x");

    if (m_Model == -1)
    {
        MessageBox(
            nullptr,
            "Skybox.x ÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩ",
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