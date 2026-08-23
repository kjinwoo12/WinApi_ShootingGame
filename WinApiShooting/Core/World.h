#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Particle.h"
#include "PlayerState.h"
#include "PowerUp.h"
#include "SessionState.h"
#include <vector>

struct World
{
    PlayerState player;
    SessionState session;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<Explosion> explosions;
    std::vector<PowerUp> powerUps;
    std::vector<Particle> particles;

    void reserveDefaults()
    {
        enemies.reserve(64);
        bullets.reserve(256);
        explosions.reserve(64);
        powerUps.reserve(32);
        particles.reserve(256);
    }

    void clearEntities()
    {
        enemies.clear();
        bullets.clear();
        explosions.clear();
        powerUps.clear();
        particles.clear();
    }

    void resetRun()
    {
        const int keepHigh = session.highScore;
        clearEntities();
        player = PlayerState{};
        player.pos = {ScreenWidth * 0.5f, ScreenHeight - 100.f};
        player.invuln = 2.f;
        session = SessionState{};
        session.highScore = keepHigh;
        session.waveTimer = 0.5f;
    }
};
