#pragma once
#include "EffectsEngine.h"
#include "Random.h"
#include "World.h"

class PlayingSession
{
public:
    static void tickTimers(World& world, EffectsEngine& fx, RandomSource& rng,
                           float bgHeight, float dt);
    // true = GameOver.
    static bool checkPlayerDeath(World& world, EffectsEngine& fx, RandomSource& rng);
};
