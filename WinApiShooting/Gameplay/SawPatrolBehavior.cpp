#include "SawPatrolBehavior.h"

bool SawPatrolBehavior::configure(World& world, RandomSource& rng, Enemy& e) const
{
    const int wave = world.session.run.wave;
    e.hp = e.maxHp = 8.f + wave * 0.3f;
    e.vel = {(rng.nextInt(0, 1) == 0 ? -1.f : 1.f) * 90.f, rng.nextFloat(25.f, 45.f)};
    e.radius = 18.f;
    return true;
}

void SawPatrolBehavior::tick(EnemySystems&, World&, RandomSource&, Enemy& e, float dt) const
{
    e.pos += e.vel * dt;
    if (e.pos.x < 40.f)
    {
        e.pos.x = 40.f;
        e.vel.x = std::fabs(e.vel.x);
    }
    else if (e.pos.x > ScreenWidth - 40.f)
    {
        e.pos.x = ScreenWidth - 40.f;
        e.vel.x = -std::fabs(e.vel.x);
    }
}

KillOutcome SawPatrolBehavior::killOutcome(const World&) const
{
    return {300, 2, 1.f, true};
}
