#include "MidBossBehavior.h"
#include "MidBossPhases.h"

bool MidBossBehavior::configure(World&, RandomSource&, Enemy&) const
{
    return false;
}

KillOutcome MidBossBehavior::killOutcome(const World& world) const
{
    return {8000 + world.session.run.combo * 50, 0, 2.2f, false};
}

void MidBossBehavior::onKilled(EnemySystems& sys, World& world, RandomSource& rng, const Enemy& e) const
{
    RunSession& run = world.session.run;
    PresentationSession& pres = world.session.presentation;
    PlayerState& player = world.player;
    run.midBossAlive = false;
    run.midBossHpRatio = 0.f;
    sys.fx.spawnExplosion(world, rng, e.pos + Vec2{-30.f, -20.f}, 1, 1.2f);
    sys.fx.spawnExplosion(world, rng, e.pos + Vec2{30.f, 10.f}, 1, 1.1f);
    sys.fx.spawnExplosion(world, rng, e.pos + Vec2{0.f, 25.f}, 1, 1.0f);
    pres.shake = 1.2f;
    player.bombs = clampInt(player.bombs + 1, 0, 5);
    PowerUp drop;
    drop.pos = e.pos;
    drop.vel = {0.f, 60.f};
    drop.kind = PowerUpKind::Weapon;
    world.powerUps.push_back(drop);
    for (Enemy& orb : world.enemies)
    {
        if (orb.kind == EnemyKind::OrbitMine)
            orb.alive = false;
    }
}

void MidBossBehavior::tick(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e, float dt) const
{
    if (world.session.run.bossIntroActive())
    {
        MidBossPhases::tickIntro(e, world);
        return;
    }

    MidBossPhases::tickPatrol(e, dt);
    MidBossPhases::tickOrbitRespawn(world, rng, e, dt);
    MidBossPhases::tickAttack(sys, world, rng, e, world.player.pos);
}
