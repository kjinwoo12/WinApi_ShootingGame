#pragma once
#include "Common.h"

struct Explosion
{
    Vec2 pos{};
    float anim = 0.f;
    float speed = 18.f;
    int type = 0;
    int maxFrames = 11;
    float scale = 1.f;
    bool alive = true;
};
