#include "MineBurstBehavior.h"
#include "Collision.h"

bool MineBurstBehavior::configure(World& world, RandomSource& rng, Enemy& e) const
{
    const int wave = world.session.wave;
    e.hp = e.maxHp = 2.f + wave * 0.2f;
    e.vel = {rng.nextFloat(-20.f, 20.f), rng.nextFloat(30.f, 55.f)};
    e.radius = 18.f;
    return true;
}

void MineBurstBehavior::tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const
{
    e.pos += e.vel * dt;
    if (length(world.player.pos - e.pos) < 70.f)
    {
        e.alive = false;
        sys.bullets.spawnRadialBurst(world, e.pos);
        sys.fx.spawnExplosion(world, rng, e.pos, 2, 1.2f);
        world.session.shake = (std::max)(world.session.shake, 0.35f);
    }
}

KillOutcome MineBurstBehavior::killOutcome(const World&) const
{
    return {220, 2, 1.f, true};
}

void MineBurstBehavior::onKilled(EnemySystems& sys, World& world, RandomSource&, const Enemy& e) const
{
    sys.bullets.spawnRadialBurst(world, e.pos);
}
