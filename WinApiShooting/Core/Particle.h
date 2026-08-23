#pragma once
#include "Common.h"

struct Particle
{
    Vec2 pos{};
    Vec2 vel{};
    float life = 0.5f;
    float maxLife = 0.5f;
    float size = 3.f;
    Gdiplus::Color color{255, 255, 200, 80};
    bool alive = true;
};
