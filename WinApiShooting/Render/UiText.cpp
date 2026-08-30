#include "UiText.h"

void UiText::draw(Gdiplus::Graphics& g, const wchar_t* text, const Gdiplus::Font& font,
                  const Gdiplus::Brush& brush, const Gdiplus::RectF& box,
                  Gdiplus::StringAlignment horiz, Gdiplus::StringAlignment vert)
{
    Gdiplus::StringFormat fmt;
    fmt.SetAlignment(horiz);
    fmt.SetLineAlignment(vert);
    fmt.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
    g.DrawString(text, -1, &font, box, &fmt, &brush);
}
