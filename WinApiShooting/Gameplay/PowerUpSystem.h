#pragma once
#include "EffectsEngine.h"
#include "Random.h"
#include "World.h"

class PowerUpSystem
{
public:
    explicit PowerUpSystem(EffectsEngine& effects);

    void update(World& world, RandomSource& rng, float dt);

private:
    EffectsEngine& fx;
};
