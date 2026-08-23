#pragma once
#include "Assets.h"
#include "GameState.h"
#include "Random.h"
#include "World.h"

class Renderer
{
public:
    bool init();
    void shutdown();
    void draw(HDC hdc, GameState state, const World& world, const Assets& assets, RandomSource& rng);

private:
    void drawBackground(Gdiplus::Graphics& g, const World& world, const Assets& assets);

    Gdiplus::Bitmap* backBuffer = nullptr;
    Gdiplus::Graphics* backGfx = nullptr;
};
