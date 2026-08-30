#pragma once
#include "GdiplusInclude.h"

class UiText
{
public:
    static void draw(Gdiplus::Graphics& g, const wchar_t* text, const Gdiplus::Font& font,
                     const Gdiplus::Brush& brush, const Gdiplus::RectF& box,
                     Gdiplus::StringAlignment horiz = Gdiplus::StringAlignmentCenter,
                     Gdiplus::StringAlignment vert = Gdiplus::StringAlignmentCenter);
};
