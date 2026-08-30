#include "SawChaseBehavior.h"
#include "Collision.h"

bool SawChaseBehavior::configure(World& world, RandomSource& rng, Enemy& e) const
{
    const int wave = world.session.run.wave;
    e.hp = e.maxHp = 5.f + wave * 0.3f;
    e.vel = {rng.nextFloat(-40.f, 40.f), rng.nextFloat(50.f, 90.f)};
    e.radius = 18.f;
    return true;
}

void SawChaseBehavior::tick(EnemySystems&, World& world, RandomSource&, Enemy& e, float dt) const
{
    Vec2 toPlayer = world.player.pos - e.pos;
    if (length(toPlayer) > 1.f)
    {
        toPlayer = normalize(toPlayer);
        e.vel += toPlayer * (90.f * dt);
    }
    const float spd = length(e.vel);
    if (spd > 180.f)
        e.vel = e.vel * (180.f / spd);
    e.pos += e.vel * dt;
}

KillOutcome SawChaseBehavior::killOutcome(const World&) const
{
    return {280, 2, 1.f, true};
}
