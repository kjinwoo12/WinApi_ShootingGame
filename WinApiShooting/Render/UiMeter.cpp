#include "UiMeter.h"
#include "Common.h"

Gdiplus::RectF UiMeter::spriteBounds(const Sprite& sprite, float cx, float cy, float scale)
{
    const float w = sprite.width() * scale;
    const float h = sprite.height() * scale;
    return {cx - w * 0.5f, cy - h * 0.5f, w, h};
}

void UiMeter::fillSliderSlot(Gdiplus::Graphics& g, float x, float y, float w, float h, float t,
                             Gdiplus::Color color)
{
    t = clampFloat(t, 0.f, 1.f);
    const float slot = 40.f;
    const float gap = 4.f;
    const float inset = 3.f;
    const float barX = x + slot + gap + inset;
    const float barY = y + inset;
    const float barH = (std::max)(1.f, h - inset * 2.f);
    const float barW = (std::max)(0.f, w - slot - gap - inset * 2.f) * t;
    if (barW < 0.5f)
        return;
    Gdiplus::SolidBrush brush(color);
    g.FillRectangle(&brush, barX, barY, barW, barH);
}
