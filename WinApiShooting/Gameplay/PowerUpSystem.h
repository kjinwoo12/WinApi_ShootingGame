#pragma once
#include "EffectsEngine.h"
#include "Random.h"
#include "World.h"

class PowerUpSystem
{
public:
    explicit PowerUpSystem(EffectsEngine& effects);

    void trySpawnDrop(World& world, RandomSource& rng, Vec2 pos);
    void update(World& world, RandomSource& rng, float dt);

private:
    EffectsEngine& fx;
};
