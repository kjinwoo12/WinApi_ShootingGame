#pragma once
#include "GdiplusInclude.h"
#include "Assets.h"
#include "Random.h"
#include "World.h"

class Renderer
{
public:
    bool init();
    void shutdown();

    void beginFrame(const World& world, const Assets& assets, RandomSource& rng, float screenShake);
    Gdiplus::Graphics& worldGraphics();
    Gdiplus::Graphics& endWorldLayer();
    void present(HDC hdc);

private:
    void drawBackground(Gdiplus::Graphics& g, const World& world, const Assets& assets);

    Gdiplus::Bitmap* backBuffer = nullptr;
    Gdiplus::Graphics* backGfx = nullptr;
    Gdiplus::GraphicsState worldLayerState = 0;
};
