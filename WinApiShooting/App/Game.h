#pragma once
#include "Assets.h"
#include "BulletSystem.h"
#include "Combat.h"
#include "EffectsEngine.h"
#include "EnemySimulator.h"
#include "GameState.h"
#include "Input.h"
#include "PlayerController.h"
#include "PlayerWeapon.h"
#include "PowerUpSystem.h"
#include "Random.h"
#include "Renderer.h"
#include "WaveDirector.h"
#include "World.h"

class Game
{
public:
    Game();

    bool init(HWND hwnd);
    void shutdown();
    void update(float dt);
    void render(HDC hdc);
    void onKeyDown(WPARAM key);
    void onKeyUp(WPARAM key);

private:
    void updateTitle(float dt);
    void updatePlaying(float dt);
    void updateGameOver(float dt);

    HWND window = nullptr;
    Assets assets;
    Renderer renderer;
    World world;
    InputState input;
    RandomSource rng;
    GameState state = GameState::Title;

    EffectsEngine fx;
    PowerUpSystem powerUps;
    BulletSystem bullets;
    PlayerWeapon weapon;
    Combat combat;
    PlayerController player;
    EnemySimulator enemies;
    WaveDirector waves;
};
