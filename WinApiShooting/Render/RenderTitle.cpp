#include "RenderUi.h"
#include "RenderUiDraw.h"

void RenderUi::drawTitle(Gdiplus::Graphics& g, const World& world, const Assets& assets)
{
    using namespace RenderUiDraw;
    Gdiplus::SolidBrush dim(Gdiplus::Color(140, 0, 0, 12));
    g.FillRectangle(&dim, 0, 0, ScreenWidth, ScreenHeight);

    const float cx = ScreenWidth * 0.5f;

    if (assets.world.promo.valid())
    {
        assets.world.promo.drawCentered(g, cx, 168.f, 0.48f, 0.95f);
    }

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font title(&family, 40.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font sub(&family, 14.f, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    Gdiplus::Font btnFont(&family, 14.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::SolidBrush white(Gdiplus::Color(255, 245, 250, 255));
    Gdiplus::SolidBrush glow(Gdiplus::Color(255, 70, 190, 255));

    const float pulse = 0.65f + 0.35f * (0.5f + 0.5f * std::sin(world.session.titlePulse * 3.5f));
    Gdiplus::SolidBrush prompt(Gdiplus::Color(static_cast<BYTE>(255 * pulse), 200, 240, 255));

    drawLabel(g, L"SPACE RAGE", title, glow, {0.f, 286.f, static_cast<float>(ScreenWidth), 48.f});
    drawLabel(g, L"SPACE RAGE", title, white, {0.f, 288.f, static_cast<float>(ScreenWidth), 48.f});
    if (assets.ui.titleStrip.valid())
    {
        assets.ui.titleStrip.drawCentered(g, cx, 344.f, 1.2f, 0.95f);
    }

    drawLabel(g, L"WASD MOVE   SPACE/Z FIRE   SHIFT FOCUS   X/C BOMB",
              sub, white, {40.f, 372.f, ScreenWidth - 80.f, 22.f});

    Gdiplus::RectF startBox{cx - 130.f, 418.f, 260.f, 44.f};
    if (assets.ui.btnStart.valid())
    {
        const float btnScale = 1.55f;
        assets.ui.btnStart.drawCentered(g, cx, 440.f, btnScale, 0.7f + 0.3f * pulse);
        startBox = spriteBox(assets.ui.btnStart, cx, 440.f, btnScale);
    }
    drawLabel(g, L"PRESS ENTER", btnFont, prompt, startBox);

    if (world.session.highScore > 0)
    {
        wchar_t hs[64];
        swprintf_s(hs, L"HIGH SCORE  %d", world.session.highScore);
        if (assets.ui.hiStrip.valid())
        {
            assets.ui.hiStrip.drawCentered(g, cx, 492.f, 1.15f, 0.92f);
            const Gdiplus::RectF hiBox = spriteBox(assets.ui.hiStrip, cx, 492.f, 1.15f);
            drawLabel(g, hs, sub, glow, hiBox);
        }
        else
        {
            drawLabel(g, hs, sub, glow, {0.f, 480.f, static_cast<float>(ScreenWidth), 24.f});
        }
    }
}
