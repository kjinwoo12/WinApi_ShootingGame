#include "EffectsEngine.h"
#include "Collision.h"

namespace
{
constexpr int kExplosionFrames[] = {11, 9, 9};
}

void EffectsEngine::spawnExplosion(World& world, RandomSource& rng, Vec2 pos, int type, float scale)
{
    Explosion ex;
    ex.pos = pos;
    ex.type = type;
    ex.scale = scale;
    ex.speed = (type == 0) ? 22.f : 18.f;
    if (type >= 0 && type < 3)
        ex.maxFrames = kExplosionFrames[type];
    world.explosions.push_back(ex);

    for (int i = 0; i < 10; ++i)
    {
        Particle p;
        const float ang = rng.nextFloat(0.f, Pi * 2.f);
        const float spd = rng.nextFloat(40.f, 220.f);
        p.pos = pos;
        p.vel = {std::cos(ang) * spd, std::sin(ang) * spd};
        p.life = p.maxLife = rng.nextFloat(0.25f, 0.7f);
        p.size = rng.nextFloat(2.f, 6.f) * scale;
        p.color = rgba(255, static_cast<uint8_t>(rng.nextInt(120, 220)),
                       static_cast<uint8_t>(rng.nextInt(40, 100)), 255);
        world.particles.push_back(p);
    }
}

void EffectsEngine::spawnHitSparks(World& world, RandomSource& rng, Vec2 pos, bool playerHit)
{
    for (int i = 0; i < 6; ++i)
    {
        Particle p;
        const float ang = rng.nextFloat(0.f, Pi * 2.f);
        const float spd = rng.nextFloat(30.f, 140.f);
        p.pos = pos;
        p.vel = {std::cos(ang) * spd, std::sin(ang) * spd};
        p.life = p.maxLife = rng.nextFloat(0.1f, 0.3f);
        p.size = rng.nextFloat(1.5f, 3.5f);
        p.color = playerHit ? rgba(255, 80, 80, 255) : rgba(255, 220, 80, 255);
        world.particles.push_back(p);
    }
}

void EffectsEngine::spawnMuzzleSparks(World& world, RandomSource& rng, Vec2 pos)
{
    for (int i = 0; i < 3; ++i)
    {
        Particle p;
        p.pos = {pos.x + rng.nextFloat(-4.f, 4.f), pos.y};
        p.vel = {rng.nextFloat(-20.f, 20.f), rng.nextFloat(-120.f, -40.f)};
        p.life = p.maxLife = rng.nextFloat(0.08f, 0.18f);
        p.size = rng.nextFloat(2.f, 4.f);
        p.color = rgba(120, 220, 255, 220);
        world.particles.push_back(p);
    }
}

void EffectsEngine::updateExplosions(World& world, float dt)
{
    for (Explosion& ex : world.explosions)
    {
        if (!ex.alive)
            continue;
        ex.anim += dt * ex.speed;
        if (ex.anim >= static_cast<float>(ex.maxFrames))
            ex.alive = false;
    }
    world.explosions.erase(
        std::remove_if(world.explosions.begin(), world.explosions.end(),
                       [](const Explosion& e)
                       { return !e.alive; }),
        world.explosions.end());
}

void EffectsEngine::updateParticles(World& world, float dt)
{
    for (Particle& p : world.particles)
    {
        if (!p.alive)
            continue;
        p.pos += p.vel * dt;
        p.vel = p.vel * 0.98f;
        p.life -= dt;
        if (p.life <= 0.f)
            p.alive = false;
    }
    world.particles.erase(
        std::remove_if(world.particles.begin(), world.particles.end(),
                       [](const Particle& p)
                       { return !p.alive; }),
        world.particles.end());
}
