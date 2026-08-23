#pragma once
#include "EnemySystems.h"
#include "KillOutcome.h"
#include "Random.h"
#include "World.h"

class IEnemyBehavior
{
public:
    virtual ~IEnemyBehavior() = default;

    // false = spawnEnemy가 push 안 함 (MidBoss/OrbitMine 전용 스폰 경로).
    virtual bool configure(World& world, RandomSource& rng, Enemy& e) const = 0;
    virtual void tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const = 0;

    virtual KillOutcome killOutcome(const World& world) const
    {
        (void)world;
        return {};
    }
    // e.alive 이미 false. 점수·폭발·콤보는 Combat이 처리.
    virtual void onKilled(EnemySystems& sys, World& world, RandomSource& rng, const Enemy& e) const
    {
        (void)sys;
        (void)world;
        (void)rng;
        (void)e;
    }

    virtual float bombDamage() const
    {
        return 8.f;
    }
    virtual bool invulnDuringBossIntro() const
    {
        return false;
    }
    virtual bool diesOnPlayerContact() const
    {
        return true;
    }
    virtual bool isMineVisual() const
    {
        return false;
    }
    virtual bool cullOffscreen() const
    {
        return true;
    }
};
