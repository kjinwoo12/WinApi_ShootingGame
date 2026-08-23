#pragma once
#include "Assets.h"
#include "GameState.h"
#include "World.h"

class WorldDrawer
{
public:
    static void draw(Gdiplus::Graphics& g, GameState state, const World& world, const Assets& assets);
};
