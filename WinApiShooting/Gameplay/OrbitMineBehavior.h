#pragma once
#include "IEnemyBehavior.h"

class OrbitMineBehavior : public IEnemyBehavior
{
public:
    bool configure(World& world, RandomSource& rng, Enemy& e) const override;
    void tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const override;
    KillOutcome killOutcome(const World& world) const override;
    bool invulnDuringBossIntro() const override
    {
        return true;
    }
    bool isMineVisual() const override
    {
        return true;
    }
    bool cullOffscreen() const override
    {
        return false;
    }
};
