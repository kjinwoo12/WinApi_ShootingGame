#pragma once
#include "BulletOwner.h"
#include "Common.h"
#include "WeaponLevel.h"

struct Bullet
{
    Vec2 pos{};
    Vec2 vel{};
    float life = 2.f;
    float radius = 6.f;
    int damage = 1;
    int spriteIndex = -1;
    BulletOwner owner = BulletOwner::Player;
    WeaponLevel weapon = WeaponLevel::Vulcan;
    bool grazed = false;
    bool alive = true;
};
