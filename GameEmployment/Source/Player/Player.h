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

    void Damage(int damage);

    int GetHP() const;

    bool IsDead() const;

    // 現在位置を取得
    VECTOR GetPosition() const;

private:

    // 3Dモデル
    int m_Model;

    // プレイヤーの位置
    VECTOR m_Position;

    // プレイヤーの回転
    VECTOR m_Rotation;

    // プレイヤーの大きさ
    VECTOR m_Scale;

    // 現在のレーン
    // -1 = 左
    //  0 = 中央
    //  1 = 右
    int m_Lane;

    // HP
    int m_HP;
    int m_MaxHP;

    // キー入力
    bool m_OldLeft;
    bool m_OldRight;
};