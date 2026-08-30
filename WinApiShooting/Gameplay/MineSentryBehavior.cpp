#include "MineSentryBehavior.h"
#include "Collision.h"

bool MineSentryBehavior::configure(World& world, RandomSource& rng, Enemy& e) const
{
    const int wave = world.session.run.wave;
    e.hp = e.maxHp = 4.f + wave * 0.25f;
    e.vel = {0.f, rng.nextFloat(35.f, 55.f)};
    e.radius = 18.f;
    e.shootCooldown = rng.nextFloat(0.8f, 1.6f);
    return true;
}

void MineSentryBehavior::tick(EnemySystems& sys, World& world, RandomSource&, Enemy& e, float dt) const
{
    const int wave = world.session.run.wave;
    e.pos.y += e.vel.y * dt;
    e.shootCooldown -= dt;
    if (e.shootCooldown > 0.f || e.pos.y <= 0.f || e.pos.y >= ScreenHeight * 0.8f)
        return;

    const float speed = 240.f + wave * 8.f;
    sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Vulcan, e.pos, {0.f, speed}, 1);
    sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Vulcan, e.pos, {0.f, -speed}, 1);
    sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Vulcan, e.pos, {speed, 0.f}, 1);
    sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Vulcan, e.pos, {-speed, 0.f}, 1);
    e.shootCooldown = 1.6f;
}

KillOutcome MineSentryBehavior::killOutcome(const World&) const
{
    return {180, 2, 1.f, true};
}
