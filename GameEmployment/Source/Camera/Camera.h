#pragma once

#include "DxLib.h"

class Camera
{
public:

    Camera();

    void Init();

    void Update();

private:

    VECTOR m_Pos;
    VECTOR m_Target;
};