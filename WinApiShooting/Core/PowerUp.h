#pragma once
#include "Common.h"

struct PowerUp
{
    Vec2 pos{};
    Vec2 vel{};
    int type = 0;
    float life = 12.f;
    float anim = 0.f;
    bool alive = true;
};
