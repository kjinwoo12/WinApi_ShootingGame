#pragma once
#include "EffectsEngine.h"
#include "Random.h"
#include "World.h"

class GrazeSystem
{
public:
    explicit GrazeSystem(EffectsEngine& effects);

    void process(World& world, RandomSource& rng);
    void apply(World& world, RandomSource& rng, Vec2 at);

private:
    EffectsEngine& fx;
};
