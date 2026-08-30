#pragma once
#include "EffectsEngine.h"
#include "Input.h"
#include "PlayingServices.h"
#include "Random.h"
#include "World.h"

class PlayingSession
{
public:
    static bool tick(World& world, InputState& input, RandomSource& rng, EffectsEngine& fx,
                     PlayingServices& play, float bgHeight, float dt);
    static void finalizePlayerDeath(World& world, EffectsEngine& fx, RandomSource& rng);

private:
    static void tickTimers(World& world, EffectsEngine& fx, float bgHeight, float dt);
    static void syncMidBossHp(World& world);
};
