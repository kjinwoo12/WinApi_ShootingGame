#pragma once
#include "BulletSystem.h"
#include "EffectsEngine.h"
#include "Random.h"
#include "World.h"

class PlayerWeapon
{
public:
    PlayerWeapon(BulletSystem& bullets, EffectsEngine& effects);

    void fire(World& world, RandomSource& rng);

private:
    BulletSystem& bullets;
    EffectsEngine& fx;
};
