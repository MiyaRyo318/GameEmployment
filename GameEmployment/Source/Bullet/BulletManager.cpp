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

    // éÄÇÒÇæíeÇçÌèú
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

    // Enemyï˚å¸Ç÷îÚÇŒÇ∑
    VECTOR velocity = VGet(
        0.0f,
        0.0f,
        5.0f);

    bullet.Create(
        position,
        velocity);

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
            // ìGÇ…10É_ÉÅÅ[ÉW
            enemy.Damage(10);

            // íeÇè¡Ç∑
            bullet.Destroy();
        }
    }
}