#pragma once
#include "BulletSystem.h"
#include "EffectsEngine.h"
#include "Random.h"
#include "World.h"

class EnemySimulator
{
public:
    EnemySimulator(BulletSystem& bullets, EffectsEngine& effects);

    void spawnEnemy(World& world, RandomSource& rng, EnemyKind kind,
                    float x, float y, int color = -1);
    void update(World& world, RandomSource& rng, float dt);

private:
    int pickFactionColor(RandomSource& rng, int wave) const;

    BulletSystem& bullets;
    EffectsEngine& fx;
};
