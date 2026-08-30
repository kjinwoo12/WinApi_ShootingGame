#include "WorldObjects.h"
#include "Collision.h"
#include "UiText.h"

void ParticleObject::render(Gdiplus::Graphics& g) const
{
    const float a = clampFloat(particle_.life / particle_.maxLife, 0.f, 1.f);
    const Rgba8& c = particle_.color;
    Gdiplus::SolidBrush brush(Gdiplus::Color(static_cast<BYTE>(a * c.a), c.r, c.g, c.b));
    g.FillEllipse(&brush, particle_.pos.x - particle_.size * 0.5f, particle_.pos.y - particle_.size * 0.5f,
                  particle_.size, particle_.size);
}

void EnemyObject::render(Gdiplus::Graphics& g, const Assets& assets) const
{
    const float s = enemy_.drawScale;
    assets.enemyShadowSprite(enemy_)
        .drawCentered(g, enemy_.pos.x + 4.f * s, enemy_.pos.y + 10.f * s, 0.95f * s, 0.39f);
    assets.enemySprite(enemy_).drawCentered(g, enemy_.pos.x, enemy_.pos.y, s);
}

void BulletObject::render(Gdiplus::Graphics& g, const Assets& assets) const
{
    const BulletDrawParams params = assets.bulletDrawParams(bullet_);
    assets.bulletSprite(bullet_)
        .drawCentered(g, bullet_.pos.x, bullet_.pos.y, params.scale, 1.f, params.rotationDeg);
}

void ExplosionObject::render(Gdiplus::Graphics& g, const Assets& assets) const
{
    assets.explosionSprite(explosion_.type, static_cast<int>(explosion_.anim))
        .drawCentered(g, explosion_.pos.x, explosion_.pos.y, explosion_.scale);
}

void PlayerObject::render(Gdiplus::Graphics& g, const Assets& assets) const
{
    if (player_.lives <= 0)
        return;

    const bool blink = player_.invuln > 0.f && (static_cast<int>(player_.invuln * 16.f) % 2 == 0);
    if (!blink)
    {
        const int bank = bankFromVelocity(player_.vel.x);
        assets.playerShadowSprite(bank).drawCentered(g, player_.pos.x + 4.f, player_.pos.y + 10.f, 1.f, 0.47f);
        const int ei = static_cast<int>(player_.exhaustAnim) % assets.exhaustFrameCount();
        const float exScale = player_.raging() ? 1.05f : 0.85f;
        assets.exhaustSprite(ei).drawCentered(g, player_.pos.x, player_.pos.y + 30.f, exScale, 0.85f);
        assets.playerSprite(bank, player_.raging()).drawCentered(g, player_.pos.x, player_.pos.y);
    }
    if (player_.focusing)
    {
        Gdiplus::SolidBrush core(Gdiplus::Color(230, 255, 255, 255));
        g.FillEllipse(&core, player_.pos.x - 3.f, player_.pos.y - 3.f, 6.f, 6.f);
    }
}

void PowerUpObject::render(Gdiplus::Graphics& g, const Assets& assets) const
{
    const float pulse = 0.88f + 0.12f * std::sin(powerUp_.anim * 5.f);
    const float r = 12.f * pulse;
    const float cx = powerUp_.pos.x;
    const float cy = powerUp_.pos.y;

    const Sprite& frame = assets.powerUpFrame();
    if (frame.valid())
        frame.drawCentered(g, cx, cy, 0.42f, 0.9f);

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font font(&family, 10.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::RectF icon(cx - r, cy - r, r * 2.f, r * 2.f);

    switch (powerUp_.kind)
    {
    case PowerUpKind::Weapon:
    {
        Gdiplus::PointF diamond[4] = {
            {cx, cy - r},
            {cx + r, cy},
            {cx, cy + r},
            {cx - r, cy},
        };
        Gdiplus::SolidBrush fill(Gdiplus::Color(230, 60, 200, 255));
        Gdiplus::Pen edge(Gdiplus::Color(255, 200, 240, 255), 2.f);
        g.FillPolygon(&fill, diamond, 4);
        g.DrawPolygon(&edge, diamond, 4);
        Gdiplus::SolidBrush ink(Gdiplus::Color(255, 20, 20, 40));
        UiText::draw(g, L"W", font, ink, icon);
        break;
    }
    case PowerUpKind::Life:
    {
        Gdiplus::SolidBrush fill(Gdiplus::Color(230, 40, 220, 100));
        Gdiplus::Pen edge(Gdiplus::Color(255, 180, 255, 180), 2.f);
        g.FillEllipse(&fill, cx - r, cy - r, r * 2.f, r * 2.f);
        g.DrawEllipse(&edge, cx - r, cy - r, r * 2.f, r * 2.f);
        Gdiplus::Pen cross(Gdiplus::Color(255, 255, 255, 255), 3.f);
        const float arm = r * 0.5f;
        g.DrawLine(&cross, cx - arm, cy, cx + arm, cy);
        g.DrawLine(&cross, cx, cy - arm, cx, cy + arm);
        break;
    }
    case PowerUpKind::Score:
    {
        Gdiplus::PointF hex[6];
        for (int i = 0; i < 6; ++i)
        {
            const float ang = -Pi * 0.5f + i * (Pi / 3.f);
            hex[i] = {cx + std::cos(ang) * r, cy + std::sin(ang) * r};
        }
        Gdiplus::SolidBrush fill(Gdiplus::Color(230, 255, 190, 40));
        Gdiplus::Pen edge(Gdiplus::Color(255, 240, 120, 40), 2.f);
        g.FillPolygon(&fill, hex, 6);
        g.DrawPolygon(&edge, hex, 6);
        Gdiplus::SolidBrush ink(Gdiplus::Color(255, 80, 40, 0));
        UiText::draw(g, L"PTS", font, ink, icon);
        break;
    }
    case PowerUpKind::Bomb:
    {
        Gdiplus::PointF tri[3] = {
            {cx, cy - r},
            {cx + r * 0.9f, cy + r * 0.7f},
            {cx - r * 0.9f, cy + r * 0.7f},
        };
        Gdiplus::SolidBrush fill(Gdiplus::Color(230, 255, 210, 50));
        Gdiplus::Pen edge(Gdiplus::Color(255, 255, 240, 120), 2.f);
        g.FillPolygon(&fill, tri, 3);
        g.DrawPolygon(&edge, tri, 3);
        Gdiplus::SolidBrush ink(Gdiplus::Color(255, 40, 30, 0));
        UiText::draw(g, L"B", font, ink, icon);
        break;
    }
    }
}
