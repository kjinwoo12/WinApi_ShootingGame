#include "RenderUi.h"
#include "RenderUiDraw.h"

namespace
{

void drawBossHp(Gdiplus::Graphics& g, const World& world, const Assets& assets)
{
    using namespace RenderUiDraw;
    const Enemy* boss = nullptr;
    for (const Enemy& e : world.enemies)
    {
        if (e.alive && e.kind == EnemyKind::MidBoss)
        {
            boss = &e;
            break;
        }
    }
    if (!boss || !assets.ui.sliderTrack.valid())
        return;

    const float t = clampFloat(boss->hp / (std::max)(boss->maxHp, 0.001f), 0.f, 1.f);
    const float w = static_cast<float>(assets.ui.sliderTrack.width());
    const float h = static_cast<float>(assets.ui.sliderTrack.height());
    const float x = ScreenWidth * 0.5f - w * 0.5f;
    const float y = 6.f;
    assets.ui.sliderTrack.draw(g, x, y, 1.f, 0.95f);
    fillBar(g, x, y, w, h, t, Gdiplus::Color(220, 255, 70, 80));

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font font(&family, 10.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::SolidBrush ink(Gdiplus::Color(240, 255, 230, 240));
    drawLabel(g, L"CORE", font, ink, {x, y, 40.f, h});
}

} // namespace

void RenderUi::drawHud(Gdiplus::Graphics& g, const World& world, const Assets& assets)
{
    using namespace RenderUiDraw;
    const SessionState& session = world.session;
    const PlayerState& player = world.player;

    constexpr float dockH = 64.f;
    constexpr float margin = 16.f;
    constexpr float rowH = 22.f;
    const float dockY = ScreenHeight - dockH;
    const float contentW = ScreenWidth - margin * 2.f;

    Gdiplus::SolidBrush dockBg(Gdiplus::Color(200, 6, 10, 24));
    g.FillRectangle(&dockBg, 0.f, dockY, static_cast<float>(ScreenWidth), dockH);
    Gdiplus::Pen dockLine(Gdiplus::Color(120, 90, 120, 180), 1.f);
    g.DrawLine(&dockLine, 0.f, dockY, static_cast<float>(ScreenWidth), dockY);

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font font(&family, 13.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font fontSmall(&family, 11.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::SolidBrush white(Gdiplus::Color(255, 236, 244, 255));
    Gdiplus::SolidBrush accent(Gdiplus::Color(255, 110, 220, 255));
    Gdiplus::SolidBrush mute(Gdiplus::Color(210, 170, 200, 220));

    const float row1Y = dockY + 8.f;
    const float row2Y = dockY + 36.f;
    wchar_t line[128];

    const float cols[] = {130.f, 120.f, 100.f, 100.f, 48.f};
    float colX = margin;

    swprintf_s(line, L"Score : %d", session.score);
    drawLabel(g, line, font, white, {colX, row1Y, cols[0], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[0];

    swprintf_s(line, L"Best : %d", session.highScore);
    drawLabel(g, line, fontSmall, accent, {colX, row1Y, cols[1], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[1];

    swprintf_s(line, L"Stage : %d", session.sector);
    drawLabel(g, line, fontSmall, mute, {colX, row1Y, cols[2], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[2];

    swprintf_s(line, L"Wave : %d", session.wave);
    drawLabel(g, line, fontSmall, mute, {colX, row1Y, cols[3], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[3];

    {
        const Sprite* weaponSpr = &assets.world.vulcan[1];
        if (player.weapon == WeaponLevel::Plasma)
            weaponSpr = &assets.world.plasma[0];
        else if (player.weapon == WeaponLevel::Proton)
            weaponSpr = &assets.world.proton[0];
        weaponSpr->drawCentered(g, colX + 18.f, row1Y + rowH * 0.5f, 0.55f, 0.95f);
    }

    for (int i = 0; i < player.lives; ++i)
    {
        const float lx = ScreenWidth - margin - 10.f - static_cast<float>(i) * 28.f;
        const float ly = row1Y + rowH * 0.5f;
        if (assets.ui.lifeSlot.valid())
        {
            assets.ui.lifeSlot.drawCentered(g, lx, ly, 0.42f, 0.9f);
        }
        assets.world.playerBlue[2].drawCentered(g, lx, ly, 0.28f);
    }

    const float rageCap = player.raging() ? 6.f : 4.f;
    const float rageT = player.raging()
                            ? clampFloat(player.rageTimer / rageCap, 0.f, 1.f)
                            : clampFloat(player.rageGauge / 100.f, 0.f, 1.f);
    constexpr float labelW = 44.f;
    constexpr float barH = 12.f;
    constexpr float rightHudW = 110.f;
    const float barX = margin + labelW;
    const float barW = contentW - labelW - rightHudW;
    const float barY = row2Y + (rowH - barH) * 0.5f;

    Gdiplus::SolidBrush rageInk(Gdiplus::Color(230, 255, 130, 130));
    drawLabel(g, L"RAGE", fontSmall, rageInk, {margin, row2Y, labelW, rowH},
              Gdiplus::StringAlignmentNear);

    Gdiplus::SolidBrush trackBg(Gdiplus::Color(160, 20, 24, 40));
    Gdiplus::Pen trackEdge(Gdiplus::Color(180, 90, 100, 140), 1.f);
    g.FillRectangle(&trackBg, barX, barY, barW, barH);
    g.DrawRectangle(&trackEdge, barX, barY, barW, barH);

    if (rageT > 0.005f)
    {
        Gdiplus::SolidBrush fill(player.raging()
                                     ? Gdiplus::Color(230, 255, 140, 60)
                                     : Gdiplus::Color(220, 220, 55, 60));
        const float filled = (barW - 2.f) * rageT;
        g.FillRectangle(&fill, barX + 1.f, barY + 1.f, filled, barH - 2.f);
        if (player.raging() && player.rageTimer > 4.f)
        {
            Gdiplus::SolidBrush over(Gdiplus::Color(240, 255, 255, 255));
            g.FillRectangle(&over, barX + 1.f + filled - 2.f, barY + 1.f, 2.f, barH - 2.f);
        }
    }

    const wchar_t* actLabel = L"ACT I";
    Gdiplus::Color actColor(210, 170, 200, 220);
    if (session.sector <= 5)
    {
        actLabel = L"ACT I";
    }
    else if (session.sector <= 10)
    {
        actLabel = L"ACT II";
    }
    else if (session.sector <= 15)
    {
        actLabel = L"ACT III";
    }
    else
    {
        actLabel = L"EX";
        actColor = Gdiplus::Color(255, 255, 80, 90);
    }
    Gdiplus::SolidBrush actBrush(actColor);
    drawLabel(g, actLabel, fontSmall, actBrush,
              {ScreenWidth - margin - rightHudW, row2Y, 50.f, rowH},
              Gdiplus::StringAlignmentNear);

    swprintf_s(line, L"B x%d", player.bombs);
    Gdiplus::SolidBrush bombBrush(Gdiplus::Color(240, 255, 220, 80));
    drawLabel(g, line, fontSmall, bombBrush,
              {ScreenWidth - margin - 56.f, row2Y, 56.f, rowH},
              Gdiplus::StringAlignmentFar);

    if (session.midBossAlive)
    {
        drawBossHp(g, world, assets);
    }

    if (session.combo >= 2)
    {
        swprintf_s(line, L"x%d", session.combo);
        Gdiplus::SolidBrush comboBrush(Gdiplus::Color(255, 255, 210, 90));
        const float comboY = session.midBossAlive ? 30.f : 4.f;
        drawLabel(g, line, font, comboBrush,
                  {0.f, comboY, static_cast<float>(ScreenWidth), 20.f});
    }

    if (session.sectorClearTimer > 0.f)
    {
        const float cx = ScreenWidth * 0.5f;
        const float cy = ScreenHeight * 0.42f;
        if (assets.ui.btnBanner.valid())
        {
            assets.ui.btnBanner.drawCentered(g, cx, cy, 2.15f, 0.96f);
        }
        Gdiplus::Font banner(&family, 16.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::SolidBrush glow(Gdiplus::Color(255, 245, 255, 255));
        drawLabel(g, L"SECTOR CLEAR", banner, glow,
                  {0.f, cy - 12.f, static_cast<float>(ScreenWidth), 24.f});
    }
}
