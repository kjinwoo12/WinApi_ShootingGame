#pragma once
#include "Assets.h"
#include "Random.h"
#include "World.h"

class EffectsEngine
{
public:
    void spawnExplosion(World& world, RandomSource& rng, Vec2 pos, int type, float scale);
    void spawnHitSparks(World& world, RandomSource& rng, Vec2 pos, bool playerHit);
    void spawnPowerUp(World& world, RandomSource& rng, Vec2 pos);
    void spawnMuzzleSparks(World& world, RandomSource& rng, Vec2 pos);
    void updateExplosions(World& world, const Assets& assets, float dt);
    void updateParticles(World& world, float dt);
};
