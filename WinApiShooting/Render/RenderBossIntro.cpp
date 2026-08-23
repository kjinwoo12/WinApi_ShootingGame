#include "RenderUi.h"
#include "RenderUiDraw.h"

void RenderUi::drawBossIntro(Gdiplus::Graphics& g, const World& world, const Assets& assets)
{
    using namespace RenderUiDraw;
    const float t = world.session.bossIntroProgress();
    const float flash = 0.5f + 0.5f * std::sin(world.session.gameTime * 16.f);

    const BYTE dimA = static_cast<BYTE>(clampFloat(140.f * (1.f - t * 0.35f), 0.f, 180.f));
    Gdiplus::SolidBrush dim(Gdiplus::Color(dimA, 8, 0, 20));
    g.FillRectangle(&dim, 0.f, 0.f, static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight));

    const float cx = ScreenWidth * 0.5f;
    const float cy = 280.f;
    Gdiplus::RectF panel(80.f, 210.f, ScreenWidth - 160.f, 140.f);
    if (assets.ui.mainHud.valid())
    {
        assets.ui.mainHud.drawCentered(g, cx, cy, 1.55f, 0.94f);
        panel = spriteBox(assets.ui.mainHud, cx, cy, 1.55f);
    }

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font warnFont(&family, 36.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font subFont(&family, 16.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    const BYTE warnA = static_cast<BYTE>(clampFloat(220.f + 35.f * flash, 0.f, 255.f));
    Gdiplus::SolidBrush warnBrush(Gdiplus::Color(warnA, 255, 60, 70));

    Gdiplus::RectF warnBox = panel;
    warnBox.Y += 28.f;
    warnBox.Height = 48.f;
    drawLabel(g, L"WARNING", warnFont, warnBrush, warnBox);

    if (t > 0.25f)
    {
        const float fade = clampFloat((t - 0.25f) / 0.3f, 0.f, 1.f);
        Gdiplus::SolidBrush coreBrush(Gdiplus::Color(static_cast<BYTE>(230 * fade), 255, 210, 90));
        Gdiplus::RectF coreBox = panel;
        coreBox.Y += 78.f;
        coreBox.Height = 28.f;
        drawLabel(g, L"CARRIER CORE INBOUND", subFont, coreBrush, coreBox);
    }

    const float stripH = 8.f + 3.f * flash;
    Gdiplus::SolidBrush strip(Gdiplus::Color(static_cast<BYTE>(160 + 60 * flash), 255, 40, 50));
    g.FillRectangle(&strip, 0.f, 0.f, static_cast<float>(ScreenWidth), stripH);
    g.FillRectangle(&strip, 0.f, static_cast<float>(ScreenHeight) - stripH,
                    static_cast<float>(ScreenWidth), stripH);
}
