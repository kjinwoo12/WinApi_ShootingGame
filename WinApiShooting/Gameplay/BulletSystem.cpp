#include "BulletSystem.h"

void BulletSystem::spawn(World& world, BulletOwner owner, WeaponLevel weapon,
                         Vec2 pos, Vec2 vel, int damage)
{
    if (static_cast<int>(world.bullets.size()) >= 256)
        return;

    Bullet b;
    b.owner = owner;
    b.weapon = weapon;
    b.pos = pos;
    b.vel = vel;
    b.damage = damage;
    b.life = 2.5f;
    b.radius = (weapon == WeaponLevel::Proton) ? 10.f : (weapon == WeaponLevel::Plasma ? 8.f : 5.f);
    if (owner == BulletOwner::Enemy)
        b.radius = 6.f;
    world.bullets.push_back(b);
}

void BulletSystem::spawnRadialBurst(World& world, Vec2 pos)
{
    for (int i = 0; i < 8; ++i)
    {
        const float ang = (Pi * 2.f * static_cast<float>(i)) / 8.f;
        Bullet b;
        b.owner = BulletOwner::Enemy;
        b.weapon = WeaponLevel::Proton;
        b.spriteIndex = 2;
        b.pos = pos;
        b.vel = {std::cos(ang) * 220.f, std::sin(ang) * 220.f};
        b.damage = 1;
        b.life = 2.5f;
        b.radius = 6.f;
        world.bullets.push_back(b);
    }
}

void BulletSystem::update(World& world, float dt)
{
    for (Bullet& b : world.bullets)
    {
        if (!b.alive)
            continue;
        b.pos += b.vel * dt;
        b.life -= dt;
        if (b.life <= 0.f || b.pos.y < -40.f || b.pos.y > ScreenHeight + 40.f ||
            b.pos.x < -40.f || b.pos.x > ScreenWidth + 40.f)
        {
            b.alive = false;
        }
    }
    world.bullets.erase(
        std::remove_if(world.bullets.begin(), world.bullets.end(),
                       [](const Bullet& b)
                       { return !b.alive; }),
        world.bullets.end());
}
