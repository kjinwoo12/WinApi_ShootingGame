#include "PlayingSession.h"

void PlayingSession::tickTimers(World& world, EffectsEngine& fx, RandomSource& rng,
                                float bgHeight, float dt)
{
    SessionState& session = world.session;
    const float scrollMul = session.bossIntroActive() ? 0.35f : 1.f;
    session.backgroundOffset += (120.f + session.wave * 4.f) * dt * scrollMul;
    if (bgHeight > 0.f && session.backgroundOffset >= bgHeight)
    {
        session.backgroundOffset -= bgHeight;
    }

    if (session.comboTimer > 0.f)
    {
        session.comboTimer -= dt;
        if (session.comboTimer <= 0.f)
            session.combo = 0;
    }

    if (session.bossIntroActive())
    {
        session.bossIntroTimer -= dt;
        const float pulse = 0.15f + 0.1f * (0.5f + 0.5f * std::sin(session.gameTime * 14.f));
        session.shake = (std::max)(session.shake, pulse);
        if (session.bossIntroTimer <= 0.f)
        {
            session.bossIntroTimer = 0.f;
            session.shake = (std::max)(session.shake, 0.7f);
            fx.spawnHitSparks(world, rng, {ScreenWidth * 0.5f, 160.f}, false);
        }
    }

    if (session.bombFlash > 0.f)
    {
        session.bombFlash = (std::max)(0.f, session.bombFlash - dt);
    }
}

bool PlayingSession::checkPlayerDeath(World& world, EffectsEngine& fx, RandomSource& rng)
{
    SessionState& session = world.session;
    if (world.player.lives > 0 || world.player.invuln > 0.f)
        return false;
    if (session.score > session.highScore)
        session.highScore = session.score;
    fx.spawnExplosion(world, rng, world.player.pos, 0, 2.2f);
    session.shake = 1.2f;
    (void)rng;
    return true;
}
