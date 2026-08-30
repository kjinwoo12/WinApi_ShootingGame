#include "PlayingSession.h"
#include "MidBossEncounter.h"

bool PlayingSession::tick(World& world, InputState& input, RandomSource& rng, EffectsEngine& fx,
                          PlayingServices& play, float bgHeight, float dt)
{
    world.session.presentation.decayShake(dt);
    tickTimers(world, fx, bgHeight, dt);
    MidBossEncounter::tickSession(world, fx, rng, dt);

    play.player.update(world, input, rng, dt);
    play.enemies.update(world, rng, dt);
    play.bullets.update(world, dt);
    fx.updateExplosions(world, dt);
    play.powerUps.update(world, rng, dt);
    fx.updateParticles(world, dt);
    play.combat.handleCollisions(world, rng);
    play.waves.trySpawn(world, rng, dt);
    syncMidBossHp(world);

    if (world.player.lives <= 0 && world.player.invuln <= 0.f)
    {
        finalizePlayerDeath(world, fx, rng);
        return true;
    }
    return false;
}

void PlayingSession::tickTimers(World& world, EffectsEngine& fx, float bgHeight, float dt)
{
    RunSession& run = world.session.run;
    PresentationSession& pres = world.session.presentation;

    run.gameTime += dt;
    const float scrollMul = run.bossIntroActive() ? 0.35f : 1.f;
    pres.advanceScroll((120.f + run.wave * 4.f) * dt * scrollMul, bgHeight);

    if (run.comboTimer > 0.f)
    {
        run.comboTimer -= dt;
        if (run.comboTimer <= 0.f)
            run.combo = 0;
    }

    if (run.bombFlash > 0.f)
        run.bombFlash = (std::max)(0.f, run.bombFlash - dt);

    (void)fx;
}

void PlayingSession::syncMidBossHp(World& world)
{
    RunSession& run = world.session.run;
    if (!run.midBossAlive)
    {
        run.midBossHpRatio = 0.f;
        return;
    }

    for (const Enemy& e : world.enemies)
    {
        if (e.alive && e.kind == EnemyKind::MidBoss)
        {
            run.midBossHpRatio = clampFloat(e.hp / (std::max)(e.maxHp, 0.001f), 0.f, 1.f);
            return;
        }
    }
    run.midBossHpRatio = 0.f;
}

void PlayingSession::finalizePlayerDeath(World& world, EffectsEngine& fx, RandomSource& rng)
{
    SessionState& session = world.session;
    if (session.run.score > session.highScore)
        session.highScore = session.run.score;
    fx.spawnExplosion(world, rng, world.player.pos, 0, 2.2f);
    session.presentation.shake = 1.2f;
    (void)rng;
}
