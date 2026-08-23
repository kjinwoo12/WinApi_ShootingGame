#pragma once
#include "EnemySystems.h"
#include "Enemy.h"
#include "Random.h"
#include "World.h"

namespace MidBossPhases
{
void tickIntro(Enemy& e, const World& world);
void tickPatrol(Enemy& e, float dt);
void tickOrbitRespawn(World& world, RandomSource& rng, Enemy& e, float dt);
void tickAttack(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, const Vec2& playerPos);
} // namespace MidBossPhases
