#pragma once
#include "IEnemyBehavior.h"

class MineSentryBehavior : public IEnemyBehavior
{
public:
    bool configure(World& world, RandomSource& rng, Enemy& e) const override;
    void tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const override;
    KillOutcome killOutcome(const World& world) const override;
    bool isMineVisual() const override
    {
        return true;
    }
};
