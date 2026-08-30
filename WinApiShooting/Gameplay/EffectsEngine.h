#pragma once
#include "Random.h"
#include "World.h"

class EffectsEngine
{
public:
    void spawnExplosion(World& world, RandomSource& rng, Vec2 pos, int type, float scale);
    void spawnHitSparks(World& world, RandomSource& rng, Vec2 pos, bool playerHit);
    void spawnMuzzleSparks(World& world, RandomSource& rng, Vec2 pos);
    void updateExplosions(World& world, float dt);
    void updateParticles(World& world, float dt);
};
