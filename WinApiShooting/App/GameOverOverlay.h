#pragma once
#include "Assets.h"
#include "World.h"

class GameOverOverlay
{
public:
    void render(Gdiplus::Graphics& g, const World& world, const Assets& assets) const;
};
