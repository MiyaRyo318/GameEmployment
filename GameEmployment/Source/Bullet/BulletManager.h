#pragma once

#include "DxLib.h"
#include "Bullet.h"

#include <vector>

class BulletManager
{
public:

    BulletManager();

    void Init();

    void Update();

    void Draw();

    void End();

    // ƒvƒŒƒCƒ„[‚©‚ç“G‚Ö’e‚ğ”­Ë
    void ShootPlayerBullet(VECTOR position);

private:

    std::vector<Bullet> m_Bullets;
};