#pragma once

#include "DxLib.h"

class Enemy
{
public:

    Enemy();

    void Init();

    void Update();

    void Draw();

    void End();

    void StartAttack();

    int GetAttackLane() const;

    // HP
    void Damage(int damage);

    int GetHP() const;

    bool IsDead() const;

    // 当たり判定
    VECTOR GetPosition() const;
    float GetCollisionRadius() const;

    bool CanShoot();

private:

    // 3Dモデル
    int m_Model;

    // 敵の位置
    VECTOR m_Position;

    // 敵の回転
    VECTOR m_Rotation;

    // 敵の大きさ
    VECTOR m_Scale;

    // 攻撃レーン
    int m_AttackLane;

    // 攻撃タイマー
    int m_AttackTimer;

    // HP
    int m_HP;
    int m_MaxHP;

    // 移動レーン
    int m_MoveLane;

    // 移動タイマー
    int m_MoveTimer;

    // 当たり判定
    float m_CollisionRadius;

    int m_ShootTimer;
};