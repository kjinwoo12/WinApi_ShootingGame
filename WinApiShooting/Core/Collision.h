#pragma once
#include "Common.h"

inline bool circlesOverlap(Vec2 a, float ar, Vec2 b, float br)
{
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    const float r = ar + br;
    return dx * dx + dy * dy <= r * r;
}

inline int bankFromVelocity(float vx)
{
    if (vx < -120.f)
        return 0;
    if (vx < -40.f)
        return 1;
    if (vx > 120.f)
        return 4;
    if (vx > 40.f)
        return 3;
    return 2;
}
