#include "GrazeSystem.h"
#include "Collision.h"

GrazeSystem::GrazeSystem(EffectsEngine& effects)
    : fx(effects) {}

void GrazeSystem::apply(World& world, RandomSource& rng, Vec2 at)
{
    PlayerState& player = world.player;
    SessionState& session = world.session;
    session.score += 10 * (1 + session.combo / 10);
    if (player.raging())
    {
        player.rageTimer = clampFloat(player.rageTimer + 0.12f, 0.f, 6.f);
    }
    else
    {
        player.rageGauge = clampFloat(player.rageGauge + 1.2f, 0.f, 100.f);
    }
    fx.spawnHitSparks(world, rng, at, false);
    for (int i = 0; i < 2; ++i)
    {
        Particle p;
        p.pos = at;
        p.vel = {rng.nextFloat(-40.f, 40.f), rng.nextFloat(-40.f, 40.f)};
        p.life = p.maxLife = 0.15f;
        p.size = 2.5f;
        p.color = Gdiplus::Color(255, 255, 230, 80);
        world.particles.push_back(p);
    }
}

void GrazeSystem::process(World& world, RandomSource& rng)
{
    PlayerState& player = world.player;
    if (player.lives <= 0)
        return;

    constexpr float grazeInner = 8.f;
    constexpr float grazeOuter = 22.f;

    for (Bullet& b : world.bullets)
    {
        if (!b.alive || b.owner != BulletOwner::Enemy || b.grazed)
            continue;
        const float dist = length(b.pos - player.pos);
        if (dist > grazeInner && dist < grazeOuter)
        {
            b.grazed = true;
            apply(world, rng, b.pos);
        }
    }
}
