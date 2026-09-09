#pragma once

#include "DxLib.h"
#include "Bullet.h"
#include "../Enemy/Enemy.h"
#include "../Player/Player.h"

#include <vector>

class BulletManager
{
public:

    BulletManager();

    void Init();

    void Update();

    void Draw();

    void End();

    // プレイヤーから敵へ弾を発射
    void ShootPlayerBullet(VECTOR position);

    // 敵からプレイヤーへ弾を発射
    void ShootEnemyBullet(VECTOR position, int lane);

    // プレイヤー弾と敵の当たり判定
    void CheckEnemyCollision(Enemy& enemy);

    // 敵弾とプレイヤーの当たり判定
    void CheckPlayerCollision(Player& player);

private:

    std::vector<Bullet> m_Bullets;
};