#pragma once
#include "GdiplusInclude.h"
#include "Sprite.h"

class UiMeter
{
public:
    static Gdiplus::RectF spriteBounds(const Sprite& sprite, float cx, float cy, float scale);
    static void fillSliderSlot(Gdiplus::Graphics& g, float x, float y, float w, float h, float t,
                               Gdiplus::Color color);
};
