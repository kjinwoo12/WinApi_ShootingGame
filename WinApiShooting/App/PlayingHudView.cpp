#include "PlayingHudView.h"
#include "UiMeter.h"
#include "UiText.h"

void PlayingHudView::render(Gdiplus::Graphics& g, const World& world, const Assets& assets) const
{
    renderDock(g, world, assets);
    if (world.session.run.bossIntroActive())
        renderBossIntro(g, world, assets);
    renderBombFlash(g, world);
}

void PlayingHudView::renderBombFlash(Gdiplus::Graphics& g, const World& world) const
{
    if (world.session.run.bombFlash <= 0.f)
        return;

    const BYTE a = static_cast<BYTE>(clampFloat(90.f * (world.session.run.bombFlash / 0.25f), 0.f, 90.f));
    Gdiplus::SolidBrush flash(Gdiplus::Color(a, 255, 255, 255));
    g.FillRectangle(&flash, 0.f, 0.f, static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight));
}

void PlayingHudView::renderDock(Gdiplus::Graphics& g, const World& world, const Assets& assets) const
{
    const RunSession& run = world.session.run;
    const int highScore = world.session.highScore;
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

    swprintf_s(line, L"Score : %d", run.score);
    UiText::draw(g, line, font, white, {colX, row1Y, cols[0], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[0];

    swprintf_s(line, L"Best : %d", highScore);
    UiText::draw(g, line, fontSmall, accent, {colX, row1Y, cols[1], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[1];

    swprintf_s(line, L"Stage : %d", run.sector);
    UiText::draw(g, line, fontSmall, mute, {colX, row1Y, cols[2], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[2];

    swprintf_s(line, L"Wave : %d", run.wave);
    UiText::draw(g, line, fontSmall, mute, {colX, row1Y, cols[3], rowH}, Gdiplus::StringAlignmentNear);
    colX += cols[3];

    assets.hudWeaponIcon(player.weapon)
        .drawCentered(g, colX + 18.f, row1Y + rowH * 0.5f, 0.55f, 0.95f);

    for (int i = 0; i < player.lives; ++i)
    {
        const float lx = ScreenWidth - margin - 10.f - static_cast<float>(i) * 28.f;
        const float ly = row1Y + rowH * 0.5f;
        const Sprite& slot = assets.hudLifeSlot();
        if (slot.valid())
            slot.drawCentered(g, lx, ly, 0.42f, 0.9f);
        assets.hudLifeShip().drawCentered(g, lx, ly, 0.28f);
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
    UiText::draw(g, L"RAGE", fontSmall, rageInk, {margin, row2Y, labelW, rowH},
                 Gdiplus::StringAlignmentNear);

    Gdiplus::SolidBrush trackBg(Gdiplus::Color(160, 20, 24, 40));
    Gdiplus::Pen trackEdge(Gdiplus::Color(180, 90, 100, 140), 1.f);
    g.FillRectangle(&trackBg, barX, barY, barW, barH);
    g.DrawRectangle(&trackEdge, barX, barY, barW, barH);

    if (rageT > 0.005f)
    {
        Gdiplus::SolidBrush fill(player.raging() ? Gdiplus::Color(230, 255, 140, 60)
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
    if (run.sector <= 5)
        actLabel = L"ACT I";
    else if (run.sector <= 10)
        actLabel = L"ACT II";
    else if (run.sector <= 15)
        actLabel = L"ACT III";
    else
    {
        actLabel = L"EX";
        actColor = Gdiplus::Color(255, 255, 80, 90);
    }
    Gdiplus::SolidBrush actBrush(actColor);
    UiText::draw(g, actLabel, fontSmall, actBrush,
                 {ScreenWidth - margin - rightHudW, row2Y, 50.f, rowH},
                 Gdiplus::StringAlignmentNear);

    swprintf_s(line, L"B x%d", player.bombs);
    Gdiplus::SolidBrush bombBrush(Gdiplus::Color(240, 255, 220, 80));
    UiText::draw(g, line, fontSmall, bombBrush, {ScreenWidth - margin - 56.f, row2Y, 56.f, rowH},
                 Gdiplus::StringAlignmentFar);

    if (run.midBossAlive)
        renderBossHp(g, world, assets);

    if (run.combo >= 2)
    {
        swprintf_s(line, L"x%d", run.combo);
        Gdiplus::SolidBrush comboBrush(Gdiplus::Color(255, 255, 210, 90));
        const float comboY = run.midBossAlive ? 30.f : 4.f;
        UiText::draw(g, line, font, comboBrush, {0.f, comboY, static_cast<float>(ScreenWidth), 20.f});
    }

    if (run.sectorClearTimer > 0.f)
    {
        const float cx = ScreenWidth * 0.5f;
        const float cy = ScreenHeight * 0.42f;
        const Sprite& banner = assets.hudSectorBanner();
        if (banner.valid())
            banner.drawCentered(g, cx, cy, 2.15f, 0.96f);
        Gdiplus::Font bannerFont(&family, 16.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::SolidBrush glow(Gdiplus::Color(255, 245, 255, 255));
        UiText::draw(g, L"SECTOR CLEAR", bannerFont, glow, {0.f, cy - 12.f, static_cast<float>(ScreenWidth), 24.f});
    }
}

void PlayingHudView::renderBossHp(Gdiplus::Graphics& g, const World& world, const Assets& assets) const
{
    const Sprite& track = assets.hudBossTrack();
    if (!track.valid())
        return;

    const float t = world.session.run.midBossHpRatio;
    const float w = static_cast<float>(track.width());
    const float h = static_cast<float>(track.height());
    const float x = ScreenWidth * 0.5f - w * 0.5f;
    const float y = 6.f;
    track.draw(g, x, y, 1.f, 0.95f);
    UiMeter::fillSliderSlot(g, x, y, w, h, t, Gdiplus::Color(220, 255, 70, 80));

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font font(&family, 10.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::SolidBrush ink(Gdiplus::Color(240, 255, 230, 240));
    UiText::draw(g, L"CORE", font, ink, {x, y, 40.f, h});
}

void PlayingHudView::renderBossIntro(Gdiplus::Graphics& g, const World& world, const Assets& assets) const
{
    const float t = world.session.run.bossIntroProgress();
    const float flash = 0.5f + 0.5f * std::sin(world.session.run.gameTime * 16.f);

    const BYTE dimA = static_cast<BYTE>(clampFloat(140.f * (1.f - t * 0.35f), 0.f, 180.f));
    Gdiplus::SolidBrush dim(Gdiplus::Color(dimA, 8, 0, 20));
    g.FillRectangle(&dim, 0.f, 0.f, static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight));

    const float cx = ScreenWidth * 0.5f;
    const float cy = 280.f;
    Gdiplus::RectF panel(80.f, 210.f, ScreenWidth - 160.f, 140.f);
    const Sprite& hudPanel = assets.hudPanel();
    if (hudPanel.valid())
    {
        hudPanel.drawCentered(g, cx, cy, 1.55f, 0.94f);
        panel = UiMeter::spriteBounds(hudPanel, cx, cy, 1.55f);
    }

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font warnFont(&family, 36.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font subFont(&family, 16.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    const BYTE warnA = static_cast<BYTE>(clampFloat(220.f + 35.f * flash, 0.f, 255.f));
    Gdiplus::SolidBrush warnBrush(Gdiplus::Color(warnA, 255, 60, 70));

    Gdiplus::RectF warnBox = panel;
    warnBox.Y += 28.f;
    warnBox.Height = 48.f;
    UiText::draw(g, L"WARNING", warnFont, warnBrush, warnBox);

    if (t > 0.25f)
    {
        const float fade = clampFloat((t - 0.25f) / 0.3f, 0.f, 1.f);
        Gdiplus::SolidBrush coreBrush(Gdiplus::Color(static_cast<BYTE>(230 * fade), 255, 210, 90));
        Gdiplus::RectF coreBox = panel;
        coreBox.Y += 78.f;
        coreBox.Height = 28.f;
        UiText::draw(g, L"CARRIER CORE INBOUND", subFont, coreBrush, coreBox);
    }

    const float stripH = 8.f + 3.f * flash;
    Gdiplus::SolidBrush strip(Gdiplus::Color(static_cast<BYTE>(160 + 60 * flash), 255, 40, 50));
    g.FillRectangle(&strip, 0.f, 0.f, static_cast<float>(ScreenWidth), stripH);
    g.FillRectangle(&strip, 0.f, static_cast<float>(ScreenHeight) - stripH,
                    static_cast<float>(ScreenWidth), stripH);
}
