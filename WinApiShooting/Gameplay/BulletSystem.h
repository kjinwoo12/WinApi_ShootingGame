#pragma once
#include "Random.h"
#include "World.h"

class BulletSystem
{
public:
    void spawn(World& world, BulletOwner owner, WeaponLevel weapon,
               Vec2 pos, Vec2 vel, int damage);
    void spawnRadialBurst(World& world, Vec2 pos);
    void update(World& world, float dt);
};
