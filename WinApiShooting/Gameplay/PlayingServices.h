#pragma once
#include "BulletSystem.h"
#include "Combat.h"
#include "EffectsEngine.h"
#include "EnemySimulator.h"
#include "PlayerController.h"
#include "PlayerWeapon.h"
#include "PowerUpSystem.h"
#include "WaveDirector.h"

class PlayingServices
{
public:
    explicit PlayingServices(EffectsEngine& fx);

    PowerUpSystem powerUps;
    BulletSystem bullets;
    PlayerWeapon weapon;
    Combat combat;
    PlayerController player;
    EnemySimulator enemies;
    WaveDirector waves;
};
