#pragma once
#include "Common.h"
#include "Color.h"

struct Particle
{
    Vec2 pos{};
    Vec2 vel{};
    float life = 0.5f;
    float maxLife = 0.5f;
    float size = 3.f;
    Rgba8 color{255, 200, 80, 255};
    bool alive = true;
};
