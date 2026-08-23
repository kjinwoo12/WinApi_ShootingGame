#include "PlayerController.h"

PlayerController::PlayerController(PlayerWeapon& weaponRef, Combat& combatRef)
    : weapon(weaponRef), combat(combatRef) {}

void PlayerController::update(World& world, InputState& input, RandomSource& rng, float dt)
{
    PlayerState& player = world.player;
    SessionState& session = world.session;

    Vec2 dir{};
    if (input.moveUp())
        dir.y -= 1.f;
    if (input.moveDown())
        dir.y += 1.f;
    if (input.moveLeft())
        dir.x -= 1.f;
    if (input.moveRight())
        dir.x += 1.f;
    if (length(dir) > 0.f)
        dir = normalize(dir);

    player.focusing = input.focus();
    player.vel = dir * (player.focusing ? 220.f : 420.f);
    player.pos += player.vel * dt;
    player.pos.x = clampFloat(player.pos.x, 28.f, ScreenWidth - 28.f);
    player.pos.y = clampFloat(player.pos.y, 40.f, ScreenHeight - 78.f);

    if (player.invuln > 0.f)
        player.invuln -= dt;
    if (player.hurtFlash > 0.f)
        player.hurtFlash -= dt;
    if (player.bombTimer > 0.f)
        player.bombTimer -= dt;

    const float exhaustRate = player.raging() ? 22.f : (player.focusing ? 10.f : 16.f);
    player.exhaustAnim += dt * exhaustRate;
    player.fireCooldown -= dt;

    if (player.raging())
    {
        player.rageTimer -= dt;
        session.shake = (std::max)(session.shake, 0.08f);
        if (player.rageTimer <= 0.f)
        {
            player.rageTimer = 0.f;
            player.rageGauge = 0.f;
        }
    }
    else
    {
        if (session.combo > 0 && session.comboTimer > 0.f)
        {
            player.rageGauge = clampFloat(player.rageGauge + 4.f * dt, 0.f, 100.f);
        }
        if (player.rageGauge >= 100.f)
        {
            player.rageTimer = 4.f;
            player.rageGauge = 100.f;
        }
    }

    if (input.consumeBombEdge())
    {
        combat.detonateBomb(world, rng);
    }

    if (input.fire() && player.fireCooldown <= 0.f)
    {
        weapon.fire(world, rng);
    }
}
