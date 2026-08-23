#pragma once
#include "EnemySimulator.h"
#include "FormationId.h"
#include "Random.h"
#include "World.h"

class WaveDirector
{
public:
    explicit WaveDirector(EnemySimulator& enemies);

    void spawnFormation(World& world, RandomSource& rng, FormationId id);
    void spawnWave(World& world, RandomSource& rng);
    void trySpawn(World& world, RandomSource& rng, float dt);

private:
    EnemySimulator& enemies;
};
