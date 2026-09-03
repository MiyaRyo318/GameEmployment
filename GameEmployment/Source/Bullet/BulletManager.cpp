#include "BulletManager.h"
#include "DxLib.h"

#include <algorithm>

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