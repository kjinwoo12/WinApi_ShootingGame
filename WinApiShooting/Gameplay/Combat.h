#pragma once
#include "BulletSystem.h"
#include "EffectsEngine.h"
#include "GrazeSystem.h"
#include "Random.h"
#include "World.h"

// 충돌·킬·폭탄·피격. 탄 스폰·플레이어 발사 없음.
class Combat
{
public:
    Combat(EffectsEngine& effects, BulletSystem& bulletSys);

    void detonateBomb(World& world, RandomSource& rng);
    void handleCollisions(World& world, RandomSource& rng);
    void damagePlayer(World& world, RandomSource& rng);

private:
    void applyEnemyKill(World& world, RandomSource& rng, Enemy& e);

    EffectsEngine& fx;
    BulletSystem& bullets;
    GrazeSystem graze;
};
