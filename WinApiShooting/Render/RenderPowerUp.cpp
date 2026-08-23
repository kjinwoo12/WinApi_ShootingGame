#include "RenderUi.h"
#include "RenderUiDraw.h"

void RenderUi::drawPowerUp(Gdiplus::Graphics& g, const PowerUp& powerUp, const Assets& assets)
{
    using namespace RenderUiDraw;
    const float pulse = 0.88f + 0.12f * std::sin(powerUp.anim * 5.f);
    const float r = 12.f * pulse;
    const float cx = powerUp.pos.x;
    const float cy = powerUp.pos.y;

    if (assets.ui.hexFrame.valid())
    {
        assets.ui.hexFrame.drawCentered(g, cx, cy, 0.42f, 0.9f);
    }

    Gdiplus::FontFamily family(L"Segoe UI");
    Gdiplus::Font font(&family, 10.f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::RectF icon(cx - r, cy - r, r * 2.f, r * 2.f);

    if (powerUp.type == 0)
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
        drawLabel(g, L"W", font, ink, icon);
    }
    else if (powerUp.type == 1)
    {
        Gdiplus::SolidBrush fill(Gdiplus::Color(230, 40, 220, 100));
        Gdiplus::Pen edge(Gdiplus::Color(255, 180, 255, 180), 2.f);
        g.FillEllipse(&fill, cx - r, cy - r, r * 2.f, r * 2.f);
        g.DrawEllipse(&edge, cx - r, cy - r, r * 2.f, r * 2.f);
        Gdiplus::Pen cross(Gdiplus::Color(255, 255, 255, 255), 3.f);
        const float arm = r * 0.5f;
        g.DrawLine(&cross, cx - arm, cy, cx + arm, cy);
        g.DrawLine(&cross, cx, cy - arm, cx, cy + arm);
    }
    else if (powerUp.type == 2)
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
        drawLabel(g, L"PTS", font, ink, icon);
    }
    else
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
        drawLabel(g, L"B", font, ink, icon);
    }
}
