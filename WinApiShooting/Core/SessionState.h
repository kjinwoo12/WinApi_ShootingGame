#pragma once
#include "Common.h"

struct RunSession
{
    int score = 0;
    int combo = 0;
    float comboTimer = 0.f;
    int wave = 0;
    int sector = 1;
    float waveTimer = 0.f;
    float sectorClearTimer = 0.f;
    float bossIntroTimer = 0.f;
    float bossIntroDuration = 3.5f;
    float gameTime = 0.f;
    float bombFlash = 0.f;
    int bombsUsed = 0;
    bool sectorNoHit = true;
    bool midBossAlive = false;
    float midBossHpRatio = 0.f;

    bool bossIntroActive() const
    {
        return bossIntroTimer > 0.f;
    }
    float bossIntroProgress() const
    {
        if (bossIntroDuration <= 0.001f)
            return 1.f;
        return clampFloat(1.f - bossIntroTimer / bossIntroDuration, 0.f, 1.f);
    }
};

struct PresentationSession
{
    float backgroundOffset = 0.f;
    float shake = 0.f;
    float titlePulse = 0.f;

    void advanceScroll(float speed, float bgHeight);
    void decayShake(float dt);
};

struct SessionState
{
    int highScore = 0;
    RunSession run;
    PresentationSession presentation;
};
