#pragma once
#include "IEnemyBehavior.h"

class MidBossBehavior : public IEnemyBehavior
{
public:
    bool configure(World& world, RandomSource& rng, Enemy& e) const override;
    void tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const override;
    KillOutcome killOutcome(const World& world) const override;
    void onKilled(EnemySystems& sys, World& world, RandomSource& rng, const Enemy& e) const override;
    float bombDamage() const override
    {
        return 12.f;
    }
    bool invulnDuringBossIntro() const override
    {
        return true;
    }
    bool diesOnPlayerContact() const override
    {
        return false;
    }
    bool cullOffscreen() const override
    {
        return false;
    }
};
