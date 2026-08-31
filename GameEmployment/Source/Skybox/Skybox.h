#pragma once

#include "DxLib.h"

class Skybox
{
public:

    Skybox();

    void Init();
    void Update();
    void Draw();
    void End();

private:

    int m_Model;

    VECTOR m_Position;
    VECTOR m_Rotation;
    VECTOR m_Scale;
};