#pragma once
#include "Assets.h"
#include "BulletSystem.h"
#include "Combat.h"
#include "EffectsEngine.h"
#include "EnemySimulator.h"
#include "Input.h"
#include "PlayerController.h"
#include "PlayerWeapon.h"
#include "PowerUpSystem.h"
#include "Random.h"
#include "Renderer.h"
#include "WaveDirector.h"
#include "World.h"

struct SceneContext
{
    SceneContext();

    HWND window = nullptr;
    Assets assets;
    Renderer renderer;
    World world;
    InputState input;
    RandomSource rng;

    EffectsEngine fx;
    PowerUpSystem powerUps;
    BulletSystem bullets;
    PlayerWeapon weapon;
    Combat combat;
    PlayerController player;
    EnemySimulator enemies;
    WaveDirector waves;
};
