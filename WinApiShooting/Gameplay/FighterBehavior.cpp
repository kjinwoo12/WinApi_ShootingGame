#include "FighterBehavior.h"
#include "Collision.h"

bool FighterBehavior::configure(World& world, RandomSource& rng, Enemy& e) const
{
    const int wave = world.session.wave;
    float hp = 5.f + wave * 0.4f;
    float vy = rng.nextFloat(60.f, 100.f) + wave * 4.f;
    if (e.color == 2)
    {
        hp += 1.5f;
        vy *= 1.15f;
    }
    e.hp = e.maxHp = hp;
    e.vel = {0.f, vy};
    e.radius = 18.f;
    e.shootCooldown = rng.nextFloat(0.6f, 1.4f);
    return true;
}

void FighterBehavior::tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const
{
    const int wave = world.session.wave;
    const Vec2 playerPos = world.player.pos;

    if (e.color == 0)
    {
        e.vel.x = clampFloat((e.homeX - e.pos.x) * 3.5f, -80.f, 80.f);
    }
    else
    {
        const float chase = (e.color == 2) ? 180.f : 120.f;
        const float maxVx = (e.color == 2) ? 200.f : 160.f;
        const Vec2 toPlayer = playerPos - e.pos;
        e.vel.x = clampFloat(e.vel.x + (toPlayer.x > 0 ? 1.f : -1.f) * chase * dt, -maxVx, maxVx);
    }
    e.pos += e.vel * dt;
    e.shootCooldown -= dt;
    if (e.shootCooldown > 0.f || e.pos.y <= 20.f)
        return;

    const Vec2 muzzle = e.pos + Vec2{0.f, 16.f};
    const float speed = 320.f + wave * 12.f;
    if (e.color == 0)
    {
        sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Plasma,
                          muzzle, {0.f, speed}, 1);
        e.shootCooldown = rng.nextFloat(0.9f, 1.5f);
        return;
    }

    Vec2 dir = playerPos - e.pos;
    if (length(dir) < 0.1f)
        dir = {0.f, 1.f};
    else
        dir = normalize(dir);

    if (e.color == 2)
    {
        const float baseAng = std::atan2(dir.y, dir.x);
        for (int i = -1; i <= 1; ++i)
        {
            const float ang = baseAng + static_cast<float>(i) * (18.f * Pi / 180.f);
            sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Plasma,
                              muzzle, {std::cos(ang) * speed, std::sin(ang) * speed}, 1);
        }
        e.shootCooldown = rng.nextFloat(0.6f, 1.2f);
    }
    else
    {
        sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Plasma,
                          muzzle, dir * speed, 1);
        e.shootCooldown = rng.nextFloat(0.7f, 1.5f);
    }
}

KillOutcome FighterBehavior::killOutcome(const World&) const
{
    return {250, 1, 1.4f, true};
}
