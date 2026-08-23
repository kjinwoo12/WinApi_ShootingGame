#include "WorldDrawer.h"
#include "Collision.h"
#include "RenderUi.h"

void WorldDrawer::draw(Gdiplus::Graphics& g, GameState state, const World& world, const Assets& assets)
{
    for (const Particle& p : world.particles)
    {
        if (!p.alive)
            continue;
        const float a = clampFloat(p.life / p.maxLife, 0.f, 1.f);
        Gdiplus::SolidBrush brush(Gdiplus::Color(
            static_cast<BYTE>(a * p.color.GetA()), p.color.GetR(), p.color.GetG(), p.color.GetB()));
        g.FillEllipse(&brush, p.pos.x - p.size * 0.5f, p.pos.y - p.size * 0.5f, p.size, p.size);
    }

    for (const Enemy& e : world.enemies)
    {
        if (!e.alive)
            continue;
        const float s = e.drawScale;
        assets.enemyShadowSprite(e).drawCentered(g, e.pos.x + 4.f * s, e.pos.y + 10.f * s, 0.95f * s, 0.39f);
        assets.enemySprite(e).drawCentered(g, e.pos.x, e.pos.y, s);
    }

    for (const PowerUp& p : world.powerUps)
    {
        if (!p.alive)
            continue;
        RenderUi::drawPowerUp(g, p, assets);
    }

    for (const Bullet& b : world.bullets)
    {
        if (!b.alive)
            continue;
        float rot = 0.f;
        if (std::fabs(b.vel.x) > 1.f || std::fabs(b.vel.y) > 1.f)
        {
            rot = std::atan2(b.vel.y, b.vel.x) * (180.f / Pi) + 90.f;
        }
        const float scale = (b.weapon == WeaponLevel::Proton) ? 1.6f : (b.weapon == WeaponLevel::Plasma) ? 1.3f
                                                                                                         : 1.8f;
        assets.bulletSprite(b).drawCentered(g, b.pos.x, b.pos.y, scale, 1.f, rot);
    }

    const PlayerState& player = world.player;
    if (state == GameState::Playing || state == GameState::Title)
    {
        if (state == GameState::Title)
        {
            const Vec2 demoPos{ScreenWidth * 0.5f, ScreenHeight * 0.80f};
            const int bank = 2;
            assets.playerShadowSprite(bank).drawCentered(g, demoPos.x + 10.f, demoPos.y + 14.f, 1.f, 0.45f);
            const int ei = static_cast<int>(player.exhaustAnim) % assets.world.exhaust.count();
            assets.world.exhaust.at(ei).drawCentered(g, demoPos.x, demoPos.y + 30.f, 0.9f, 0.9f);
            assets.playerSprite(bank, false).drawCentered(g, demoPos.x, demoPos.y);
        }
        else if (player.lives > 0)
        {
            const bool blink = player.invuln > 0.f && (static_cast<int>(player.invuln * 16.f) % 2 == 0);
            if (!blink)
            {
                const int bank = bankFromVelocity(player.vel.x);
                assets.playerShadowSprite(bank).drawCentered(g, player.pos.x + 4.f, player.pos.y + 10.f, 1.f, 0.47f);
                const int ei = static_cast<int>(player.exhaustAnim) % assets.world.exhaust.count();
                const float exScale = player.raging() ? 1.05f : 0.85f;
                assets.world.exhaust.at(ei).drawCentered(g, player.pos.x, player.pos.y + 30.f, exScale, 0.85f);
                assets.playerSprite(bank, player.raging()).drawCentered(g, player.pos.x, player.pos.y);
            }
            if (player.focusing)
            {
                Gdiplus::SolidBrush core(Gdiplus::Color(230, 255, 255, 255));
                g.FillEllipse(&core, player.pos.x - 3.f, player.pos.y - 3.f, 6.f, 6.f);
            }
        }
    }

    for (const Explosion& ex : world.explosions)
    {
        if (!ex.alive)
            continue;
        assets.explosionSprite(ex.type, static_cast<int>(ex.anim))
            .drawCentered(g, ex.pos.x, ex.pos.y, ex.scale);
    }
}
