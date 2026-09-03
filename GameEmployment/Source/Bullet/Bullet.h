#pragma once

#include "DxLib.h"

class Bullet
{
public:

    Bullet();

    // 弾を作成
    void Create(
        VECTOR position,
        VECTOR velocity);

    // 更新
    void Update();

    // 描画
    void Draw();

    // 画面外などで消すか
    bool IsDead() const;

private:

    // 弾の位置
    VECTOR m_Position;

    // 弾の速度
    VECTOR m_Velocity;

    // 弾の大きさ
    float m_Radius;

    // 生存フラグ
    bool m_Dead;
};