#include "Renderer.h"

bool Renderer::init()
{
    backBuffer = new Gdiplus::Bitmap(ScreenWidth, ScreenHeight, PixelFormat32bppPARGB);
    backGfx = Gdiplus::Graphics::FromImage(backBuffer);
    backGfx->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
    backGfx->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
    backGfx->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
    backGfx->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
    return backBuffer != nullptr && backGfx != nullptr;
}

void Renderer::shutdown()
{
    delete backGfx;
    backGfx = nullptr;
    delete backBuffer;
    backBuffer = nullptr;
}

void Renderer::beginFrame(const World& world, const Assets& assets, RandomSource& rng, float screenShake)
{
    if (!backGfx || !backBuffer)
        return;

    Gdiplus::Graphics& g = *backGfx;
    g.Clear(Gdiplus::Color(255, 4, 6, 18));

    const float shakeX = (screenShake > 0.f) ? rng.nextFloat(-screenShake, screenShake) * 10.f : 0.f;
    const float shakeY = (screenShake > 0.f) ? rng.nextFloat(-screenShake, screenShake) * 10.f : 0.f;

    worldLayerState = g.Save();
    g.TranslateTransform(shakeX, shakeY);
    drawBackground(g, world, assets);
}

Gdiplus::Graphics& Renderer::worldGraphics()
{
    return *backGfx;
}

Gdiplus::Graphics& Renderer::endWorldLayer()
{
    if (backGfx)
        backGfx->Restore(worldLayerState);
    return *backGfx;
}

void Renderer::present(HDC hdc)
{
    if (!backGfx || !backBuffer)
        return;

    Gdiplus::Graphics screen(hdc);
    screen.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
    screen.DrawImage(backBuffer, 0, 0, ScreenWidth, ScreenHeight);
}

void Renderer::drawBackground(Gdiplus::Graphics& g, const World& world, const Assets& assets)
{
    const float h = assets.backgroundHeight();
    const float y0 = std::fmod(world.session.presentation.backgroundOffset, h) - h;
    const Sprite& bg = assets.backgroundSprite();
    bg.draw(g, 0.f, y0, 1.f);
    bg.draw(g, 0.f, y0 + h, 1.f);

    Gdiplus::LinearGradientBrush bottom(
        Gdiplus::PointF(0, static_cast<Gdiplus::REAL>(ScreenHeight - 88)),
        Gdiplus::PointF(0, static_cast<Gdiplus::REAL>(ScreenHeight)),
        Gdiplus::Color(0, 0, 0, 0), Gdiplus::Color(180, 0, 0, 0));
    g.FillRectangle(&bottom, 0.f, static_cast<float>(ScreenHeight - 88),
                    static_cast<float>(ScreenWidth), 88.f);
}
