#include "Renderer.h"
#include "RenderUi.h"
#include "WorldDrawer.h"

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

void Renderer::draw(HDC hdc, GameState state, const World& world, const Assets& assets, RandomSource& rng)
{
    if (!backGfx || !backBuffer)
        return;

    Gdiplus::Graphics& g = *backGfx;
    g.Clear(Gdiplus::Color(255, 4, 6, 18));

    const float shake = world.session.shake;
    const float shakeX = (shake > 0.f) ? rng.nextFloat(-shake, shake) * 10.f : 0.f;
    const float shakeY = (shake > 0.f) ? rng.nextFloat(-shake, shake) * 10.f : 0.f;

    Gdiplus::GraphicsState saved = g.Save();
    g.TranslateTransform(shakeX, shakeY);
    drawBackground(g, world, assets);
    WorldDrawer::draw(g, state, world, assets);
    g.Restore(saved);

    if (state == GameState::Title)
        RenderUi::drawTitle(g, world, assets);
    else if (state == GameState::GameOver)
        RenderUi::drawGameOver(g, world, assets);
    else
    {
        RenderUi::drawHud(g, world, assets);
        if (world.session.bossIntroActive())
            RenderUi::drawBossIntro(g, world, assets);
    }

    if (world.session.bombFlash > 0.f)
    {
        const BYTE a = static_cast<BYTE>(clampFloat(90.f * (world.session.bombFlash / 0.25f), 0.f, 90.f));
        Gdiplus::SolidBrush flash(Gdiplus::Color(a, 255, 255, 255));
        g.FillRectangle(&flash, 0.f, 0.f, static_cast<float>(ScreenWidth),
                        static_cast<float>(ScreenHeight));
    }

    Gdiplus::Graphics screen(hdc);
    screen.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
    screen.DrawImage(backBuffer, 0, 0, ScreenWidth, ScreenHeight);
}

void Renderer::drawBackground(Gdiplus::Graphics& g, const World& world, const Assets& assets)
{
    const float h = static_cast<float>(assets.world.background.height());
    const float y0 = -std::fmod(world.session.backgroundOffset, h);
    assets.world.background.draw(g, 0.f, y0, 1.f);
    assets.world.background.draw(g, 0.f, y0 + h, 1.f);

    Gdiplus::LinearGradientBrush bottom(
        Gdiplus::PointF(0, static_cast<Gdiplus::REAL>(ScreenHeight - 88)),
        Gdiplus::PointF(0, static_cast<Gdiplus::REAL>(ScreenHeight)),
        Gdiplus::Color(0, 0, 0, 0), Gdiplus::Color(180, 0, 0, 0));
    g.FillRectangle(&bottom, 0.f, static_cast<float>(ScreenHeight - 88),
                    static_cast<float>(ScreenWidth), 88.f);
}
