#pragma once
#include "Common.h"
#include "WeaponLevel.h"

struct PlayerState
{
    Vec2 pos{350.f, 680.f};
    Vec2 vel{};
    float radius = 8.f;
    float fireCooldown = 0.f;
    float invuln = 0.f;
    float hurtFlash = 0.f;
    float exhaustAnim = 0.f;
    float rageGauge = 0.f;
    float rageTimer = 0.f;
    float bombTimer = 0.f;
    int lives = 3;
    int bombs = 3;
    WeaponLevel weapon = WeaponLevel::Vulcan;
    int weaponKills = 0;
    bool focusing = false;

    bool raging() const
    {
        return rageTimer > 0.f;
    }
    bool bombing() const
    {
        return bombTimer > 0.f;
    }
};
