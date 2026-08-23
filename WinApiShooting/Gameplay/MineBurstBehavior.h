#pragma once
#include "IEnemyBehavior.h"

class MineBurstBehavior : public IEnemyBehavior
{
public:
    bool configure(World& world, RandomSource& rng, Enemy& e) const override;
    void tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const override;
    KillOutcome killOutcome(const World& world) const override;
    void onKilled(EnemySystems& sys, World& world, RandomSource& rng, const Enemy& e) const override;
    bool isMineVisual() const override
    {
        return true;
    }
};
