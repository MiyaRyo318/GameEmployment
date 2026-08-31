#pragma once

#include "DxLib.h"

class Player
{
public:

    Player();

    void Init();

    void Update();

    void Draw();

    void End();

    // ダメージ
    void Damage(int damage);

    // HP取得
    int GetHP() const;

    // 死亡判定
    bool IsDead() const;

private:

    // プレイヤーの位置
    VECTOR m_Position;

    // プレイヤーのレーン
    int m_Lane;

    // HP
    int m_HP;

    // 最大HP
    int m_MaxHP;

    bool m_OldLeft;
    bool m_OldRight;
};