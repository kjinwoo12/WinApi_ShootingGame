#include "GameOverOverlay.h"
#include "UiMeter.h"
#include "UiText.h"

void GameOverOverlay::render(Gdiplus::Graphics& g, const World& world, const Assets& assets) const
{
    Gdiplus::SolidBrush dim(Gdiplus::Color(180, 0, 0, 0));
    g.FillRectangle(&dim, 0, 0, ScreenWidth, ScreenHeight);

    const float cx = ScreenWidth * 0.5f;
    const float cy = 400.f;
    Gdiplus::RectF panel{cx - 151.f, cy - 201.f, 302.f, 403.f};
    const Sprite& result = assets.resultPanel();
    if (result.valid())
    {
        result.drawCentered(g, cx, cy, 1.f, 0.96f);
        panel = UiMeter::spriteBounds(result, cx, cy, 1.f);
    }

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font title(&family, 28.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font sub(&family, 16.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::SolidBrush white(Gdiplus::Color(255, 255, 240, 240));
    Gdiplus::SolidBrush red(Gdiplus::Color(255, 255, 90, 110));
    Gdiplus::SolidBrush accent(Gdiplus::Color(255, 140, 220, 255));

    const float inset = 28.f;
    Gdiplus::RectF inner = panel;
    inner.X += inset;
    inner.Width -= inset * 2.f;

    Gdiplus::RectF titleBox = inner;
    titleBox.Y += 36.f;
    titleBox.Height = 40.f;
    UiText::draw(g, L"GAME OVER", title, red, titleBox);

    wchar_t line[64];
    swprintf_s(line, L"SCORE  %d", world.session.run.score);
    Gdiplus::RectF scoreBox = inner;
    scoreBox.Y += 120.f;
    scoreBox.Height = 28.f;
    UiText::draw(g, line, sub, white, scoreBox);

    swprintf_s(line, L"WAVE  %d", world.session.run.wave);
    Gdiplus::RectF waveBox = inner;
    waveBox.Y += 156.f;
    waveBox.Height = 24.f;
    UiText::draw(g, line, sub, accent, waveBox);

    swprintf_s(line, L"BEST  %d", world.session.highScore);
    Gdiplus::RectF bestBox = inner;
    bestBox.Y += 184.f;
    bestBox.Height = 24.f;
    UiText::draw(g, line, sub, accent, bestBox);

    Gdiplus::RectF enterBox = inner;
    enterBox.Y = panel.Y + panel.Height - 72.f;
    enterBox.Height = 28.f;
    UiText::draw(g, L"PRESS ENTER", sub, white, enterBox);
}
