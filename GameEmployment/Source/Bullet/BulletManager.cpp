#include "BulletManager.h"
#include "DxLib.h"

#include <algorithm>
#include <cmath>

BulletManager::BulletManager()
{
}

void BulletManager::Init()
{
    m_Bullets.clear();
}

void BulletManager::Update()
{
    for (auto& bullet : m_Bullets)
    {
        bullet.Update();
    }

    // 死んだ弾を削除
    m_Bullets.erase(
        std::remove_if(
            m_Bullets.begin(),
            m_Bullets.end(),
            [](const Bullet& bullet)
            {
                return bullet.IsDead();
            }),
        m_Bullets.end());
}

void BulletManager::Draw()
{
    for (auto& bullet : m_Bullets)
    {
        bullet.Draw();
    }
}

void BulletManager::End()
{
    m_Bullets.clear();
}

void BulletManager::ShootPlayerBullet(VECTOR position)
{
    Bullet bullet;

    VECTOR velocity = VGet(
        0.0f,
        0.0f,
        5.0f);

    bullet.Create(
        position,
        velocity,
        BULLET_PLAYER);

    m_Bullets.push_back(bullet);
}

void BulletManager::CheckEnemyCollision(Enemy& enemy)
{
    if (enemy.IsDead())
    {
        return;
    }

    VECTOR enemyPos = enemy.GetPosition();
    float enemyRadius = enemy.GetCollisionRadius();

    for (auto& bullet : m_Bullets)
    {
        // プレイヤー弾以外は無視
        if (bullet.GetOwner() != BULLET_PLAYER)
        {
            continue;
        }

        if (bullet.IsDead())
        {
            continue;
        }

        VECTOR bulletPos = bullet.GetPosition();

        float dx = bulletPos.x - enemyPos.x;
        float dy = bulletPos.y - enemyPos.y;
        float dz = bulletPos.z - enemyPos.z;

        float distance = sqrtf(
            dx * dx +
            dy * dy +
            dz * dz
        );

        float bulletRadius = 10.0f;

        if (distance <= enemyRadius + bulletRadius)
        {
            // 敵に10ダメージ
            enemy.Damage(10);

            // 弾を消す
            bullet.Destroy();
        }
    }
}

void BulletManager::ShootEnemyBullet(
    VECTOR position,
    int lane)
{
    Bullet bullet;

    // 真っすぐプレイヤー方向へ飛ばす
    VECTOR velocity = VGet(
        0.0f,
        0.0f,
        -5.0f);

    bullet.Create(
        position,
        velocity,
        BULLET_ENEMY);

    m_Bullets.push_back(bullet);
}

void BulletManager::CheckPlayerCollision(Player& player)
{
    if (player.IsDead())
    {
        return;
    }

    VECTOR playerPos = player.GetPosition();

    float playerRadius =
        player.GetCollisionRadius();

    for (auto& bullet : m_Bullets)
    {
        // 敵弾以外は無視
        if (bullet.GetOwner() != BULLET_ENEMY)
        {
            continue;
        }

        if (bullet.IsDead())
        {
            continue;
        }

        VECTOR bulletPos =
            bullet.GetPosition();

        float dx =
            bulletPos.x - playerPos.x;

        float dy =
            bulletPos.y - playerPos.y;

        float dz =
            bulletPos.z - playerPos.z;

        float distance =
            sqrtf(
                dx * dx +
                dy * dy +
                dz * dz);

        float bulletRadius = 10.0f;

        if (distance <=
            playerRadius + bulletRadius)
        {
            // プレイヤーに10ダメージ
            player.Damage(10);

            // 弾を消す
            bullet.Destroy();
        }
    }
}