#include "Camera.h"

Camera::Camera()
{

}

void Camera::Init()
{
    m_Pos = VGet(0.0f, 120.0f, -300.0f);
    m_Target = VGet(0.0f, 80.0f, 0.0f);

    SetCameraPositionAndTarget_UpVecY(
        m_Pos,
        m_Target);
}

void Camera::Update()
{
    SetCameraPositionAndTarget_UpVecY(
        m_Pos,
        m_Target);
}