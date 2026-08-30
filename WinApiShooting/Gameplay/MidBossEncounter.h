#pragma once
#include "EffectsEngine.h"
#include "Random.h"
#include "World.h"

namespace MidBossEncounter
{
void begin(World& world, RandomSource& rng);
void tickSession(World& world, EffectsEngine& fx, RandomSource& rng, float dt);
}
