#include "ScoutBehavior.h"
#include "Collision.h"

bool ScoutBehavior::configure(World& world, RandomSource& rng, Enemy& e) const
{
    const int wave = world.session.run.wave;
    float hp = 2.f + wave * 0.15f;
    float vy = rng.nextFloat(90.f, 140.f) + wave * 6.f;
    if (e.color == 2)
    {
        hp += 1.f;
        vy *= 1.25f;
    }
    e.hp = e.maxHp = hp;
    e.vel = {rng.nextFloat(-20.f, 20.f), vy};
    e.radius = 16.f;
    e.shootCooldown = rng.nextFloat(1.0f, 2.0f);
    return true;
}

void ScoutBehavior::tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const
{
    const int wave = world.session.run.wave;
    const Vec2 playerPos = world.player.pos;

    if (e.color == 0)
    {
        e.vel.x = std::sin(e.phase * 2.2f) * (80.f + wave * 5.f);
    }
    else if (e.color == 1)
    {
        const float dx = playerPos.x - e.pos.x;
        e.vel.x = clampFloat(e.vel.x + (dx > 0.f ? 1.f : -1.f) * 90.f * dt, -120.f, 120.f);
    }
    else
    {
        e.vel.x = std::sin(e.phase * 3.0f) * (110.f + wave * 6.f);
    }
    e.pos += e.vel * dt;
    e.shootCooldown -= dt;
    if (e.shootCooldown > 0.f || e.pos.y <= 0.f || e.pos.y >= ScreenHeight * 0.75f)
        return;

    const float speed = 280.f + wave * 10.f;
    const Vec2 muzzle = e.pos + Vec2{0.f, 18.f};
    if (e.color == 2)
    {
        sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Vulcan,
                          muzzle + Vec2{-12.f, 0.f}, {0.f, speed}, 1);
        sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Vulcan,
                          muzzle + Vec2{12.f, 0.f}, {0.f, speed}, 1);
        e.shootCooldown = rng.nextFloat(1.2f, 2.0f);
    }
    else
    {
        sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Vulcan,
                          muzzle, {0.f, speed}, 1);
        e.shootCooldown = (e.color == 0) ? rng.nextFloat(1.6f, 2.0f) : rng.nextFloat(1.4f, 2.4f);
    }
}

KillOutcome ScoutBehavior::killOutcome(const World&) const
{
    return {100, 0, 1.f, true};
}
