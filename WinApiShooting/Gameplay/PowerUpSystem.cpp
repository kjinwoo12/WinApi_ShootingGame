#include "PowerUpSystem.h"
#include "Collision.h"

PowerUpSystem::PowerUpSystem(EffectsEngine& effects)
    : fx(effects) {}

void PowerUpSystem::update(World& world, RandomSource& rng, float dt)
{
    PlayerState& player = world.player;
    SessionState& session = world.session;

    for (PowerUp& p : world.powerUps)
    {
        if (!p.alive)
            continue;
        p.anim += dt * 6.f;
        p.pos += p.vel * dt;
        p.vel.y += 20.f * dt;
        p.life -= dt;
        if (p.life <= 0.f || p.pos.y > ScreenHeight + 40.f)
            p.alive = false;

        const float magnet = player.focusing ? 48.f : 34.f;
        if (length(p.pos - player.pos) < magnet)
        {
            if (p.type == 0)
            {
                if (player.weapon == WeaponLevel::Vulcan)
                    player.weapon = WeaponLevel::Plasma;
                else if (player.weapon == WeaponLevel::Plasma)
                    player.weapon = WeaponLevel::Proton;
                else
                {
                    session.score += 500;
                    session.combo++;
                }
            }
            else if (p.type == 1)
            {
                player.lives = clampInt(player.lives + 1, 0, 5);
            }
            else if (p.type == 2)
            {
                session.score += 300 + session.combo * 20;
            }
            else if (p.type == 3)
            {
                player.bombs = clampInt(player.bombs + 1, 0, 5);
            }
            fx.spawnHitSparks(world, rng, p.pos, false);
            p.alive = false;
        }
    }
    world.powerUps.erase(
        std::remove_if(world.powerUps.begin(), world.powerUps.end(),
                       [](const PowerUp& p)
                       { return !p.alive; }),
        world.powerUps.end());
}
