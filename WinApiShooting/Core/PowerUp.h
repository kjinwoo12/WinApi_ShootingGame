#pragma once
#include "Common.h"

enum class PowerUpKind
{
    Weapon,
    Life,
    Score,
    Bomb,
};

struct PowerUp
{
    Vec2 pos{};
    Vec2 vel{};
    PowerUpKind kind = PowerUpKind::Weapon;
    float life = 12.f;
    float anim = 0.f;
    bool alive = true;
};
