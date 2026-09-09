#pragma once

#include "DxLib.h"

enum BulletOwner
{
    BULLET_PLAYER,
    BULLET_ENEMY
};

class Bullet
{
public:

    Bullet();

    void Create(
        VECTOR position,
        VECTOR velocity,
        BulletOwner owner);

    void Update();

    void Draw();

    bool IsDead() const;

    VECTOR GetPosition() const;

    void Destroy();

    BulletOwner GetOwner() const;

private:

    VECTOR m_Position;
    VECTOR m_Velocity;

    float m_Radius;

    bool m_Dead;

    BulletOwner m_Owner;
};