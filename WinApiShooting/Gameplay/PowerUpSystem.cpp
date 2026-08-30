#include "PowerUpSystem.h"
#include "Collision.h"

PowerUpSystem::PowerUpSystem(EffectsEngine& effects)
    : fx(effects) {}

void PowerUpSystem::trySpawnDrop(World& world, RandomSource& rng, Vec2 pos)
{
    if (rng.nextFloat(0.f, 1.f) > 0.35f)
        return;
    PowerUp p;
    p.pos = pos;
    p.vel = {rng.nextFloat(-40.f, 40.f), rng.nextFloat(40.f, 90.f)};
    const float roll = rng.nextFloat(0.f, 1.f);
    if (roll < 0.38f)
        p.kind = PowerUpKind::Weapon;
    else if (roll < 0.56f)
        p.kind = PowerUpKind::Life;
    else if (roll < 0.80f)
        p.kind = PowerUpKind::Score;
    else
        p.kind = PowerUpKind::Bomb;
    world.powerUps.push_back(p);
}

void PowerUpSystem::update(World& world, RandomSource& rng, float dt)
{
    PlayerState& player = world.player;
    RunSession& run = world.session.run;

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
            switch (p.kind)
            {
            case PowerUpKind::Weapon:
                if (player.weapon == WeaponLevel::Vulcan)
                    player.weapon = WeaponLevel::Plasma;
                else if (player.weapon == WeaponLevel::Plasma)
                    player.weapon = WeaponLevel::Proton;
                else
                {
                    run.score += 500;
                    run.combo++;
                }
                break;
            case PowerUpKind::Life:
                player.lives = clampInt(player.lives + 1, 0, 5);
                break;
            case PowerUpKind::Score:
                run.score += 300 + run.combo * 20;
                break;
            case PowerUpKind::Bomb:
                player.bombs = clampInt(player.bombs + 1, 0, 5);
                break;
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
