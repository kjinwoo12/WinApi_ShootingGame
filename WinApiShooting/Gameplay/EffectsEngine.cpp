#include "EffectsEngine.h"
#include "Collision.h"

void EffectsEngine::spawnExplosion(World& world, RandomSource& rng, Vec2 pos, int type, float scale)
{
    Explosion ex;
    ex.pos = pos;
    ex.type = type;
    ex.scale = scale;
    ex.speed = (type == 0) ? 22.f : 18.f;
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
        p.color = Gdiplus::Color(255, 255, rng.nextInt(120, 220), rng.nextInt(40, 100));
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
        p.color = playerHit
                      ? Gdiplus::Color(255, 255, 80, 80)
                      : Gdiplus::Color(255, 255, 220, 80);
        world.particles.push_back(p);
    }
}

void EffectsEngine::spawnPowerUp(World& world, RandomSource& rng, Vec2 pos)
{
    if (rng.nextFloat(0.f, 1.f) > 0.35f)
        return;
    PowerUp p;
    p.pos = pos;
    p.vel = {rng.nextFloat(-40.f, 40.f), rng.nextFloat(40.f, 90.f)};
    const float roll = rng.nextFloat(0.f, 1.f);
    if (roll < 0.38f)
        p.type = 0;
    else if (roll < 0.56f)
        p.type = 1;
    else if (roll < 0.80f)
        p.type = 2;
    else
        p.type = 3;
    world.powerUps.push_back(p);
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
        p.color = Gdiplus::Color(220, 120, 220, 255);
        world.particles.push_back(p);
    }
}

void EffectsEngine::updateExplosions(World& world, const Assets& assets, float dt)
{
    for (Explosion& ex : world.explosions)
    {
        if (!ex.alive)
            continue;
        ex.anim += dt * ex.speed;
        const int frames = (ex.type == 0)   ? assets.world.explosion1.count()
                           : (ex.type == 1) ? assets.world.explosion2.count()
                                            : assets.world.explosion3.count();
        if (ex.anim >= frames)
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
