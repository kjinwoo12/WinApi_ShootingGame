#pragma once
#include "Assets.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Particle.h"
#include "PlayerState.h"
#include "PowerUp.h"

class ParticleObject
{
public:
    explicit ParticleObject(const Particle& particle) : particle_(particle) {}
    void render(Gdiplus::Graphics& g) const;

private:
    const Particle& particle_;
};

class EnemyObject
{
public:
    explicit EnemyObject(const Enemy& enemy) : enemy_(enemy) {}
    void render(Gdiplus::Graphics& g, const Assets& assets) const;

private:
    const Enemy& enemy_;
};

class PowerUpObject
{
public:
    explicit PowerUpObject(const PowerUp& powerUp) : powerUp_(powerUp) {}
    void render(Gdiplus::Graphics& g, const Assets& assets) const;

private:
    const PowerUp& powerUp_;
};

class BulletObject
{
public:
    explicit BulletObject(const Bullet& bullet) : bullet_(bullet) {}
    void render(Gdiplus::Graphics& g, const Assets& assets) const;

private:
    const Bullet& bullet_;
};

class ExplosionObject
{
public:
    explicit ExplosionObject(const Explosion& explosion) : explosion_(explosion) {}
    void render(Gdiplus::Graphics& g, const Assets& assets) const;

private:
    const Explosion& explosion_;
};

class PlayerObject
{
public:
    explicit PlayerObject(const PlayerState& player) : player_(player) {}
    void render(Gdiplus::Graphics& g, const Assets& assets) const;

private:
    const PlayerState& player_;
};
