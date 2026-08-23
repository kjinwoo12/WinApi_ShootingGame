#pragma once
#include "Combat.h"
#include "Input.h"
#include "PlayerWeapon.h"
#include "Random.h"
#include "World.h"

class PlayerController
{
public:
    PlayerController(PlayerWeapon& weapon, Combat& combat);

    void update(World& world, InputState& input, RandomSource& rng, float dt);

private:
    PlayerWeapon& weapon;
    Combat& combat;
};
