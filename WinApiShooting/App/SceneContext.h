#pragma once
#include "Assets.h"
#include "EffectsEngine.h"
#include "Input.h"
#include "Random.h"
#include "Renderer.h"
#include "World.h"
#include <memory>

class PlayingServices;

struct SceneContext
{
    SceneContext();
    ~SceneContext();

    void startPlaying();
    void stopPlaying();
    bool hasPlaying() const;
    PlayingServices& playing();
    const PlayingServices& playing() const;

    HWND window = nullptr;
    Assets assets;
    Renderer renderer;
    World world;
    InputState input;
    RandomSource rng;
    EffectsEngine fx;

private:
    std::unique_ptr<PlayingServices> playing_;
};
