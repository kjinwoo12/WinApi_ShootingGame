#include "MineSeekerBehavior.h"
#include "Collision.h"

bool MineSeekerBehavior::configure(World& world, RandomSource& rng, Enemy& e) const
{
    const int wave = world.session.wave;
    e.hp = e.maxHp = 3.f + wave * 0.25f;
    e.vel = {rng.nextFloat(-30.f, 30.f), rng.nextFloat(40.f, 80.f)};
    e.radius = 18.f;
    return true;
}

void MineSeekerBehavior::tick(EnemySystems&, World& world, RandomSource&, Enemy& e, float dt) const
{
    const Vec2 playerPos = world.player.pos;
    Vec2 toPlayer = playerPos - e.pos;
    if (length(toPlayer) > 1.f)
    {
        toPlayer = normalize(toPlayer);
        e.vel += toPlayer * (70.f * dt);
    }
    const float spd = length(e.vel);
    if (spd > 160.f)
        e.vel = e.vel * (160.f / spd);
    e.pos += e.vel * dt;
}

KillOutcome MineSeekerBehavior::killOutcome(const World&) const
{
    return {180, 2, 1.f, true};
}
