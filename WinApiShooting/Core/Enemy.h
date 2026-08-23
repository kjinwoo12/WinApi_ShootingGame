#pragma once
#include "Common.h"
#include "EnemyKind.h"

struct Enemy
{
    EnemyKind kind = EnemyKind::Scout;
    Vec2 pos{};
    Vec2 vel{};
    float hp = 1.f;
    float maxHp = 1.f;
    float radius = 22.f;
    float anim = 0.f;
    float shootCooldown = 0.f;
    float phase = 0.f;
    float homeX = 0.f;
    float drawScale = 1.f;
    float patternTimer = 0.f;
    float orbitAngle = 0.f;
    float respawnTimer = 0.f;
    int color = 0; // 0=b 규율, 1=g 사냥, 2=r 광전
    int bank = 0;
    int patternStep = 0;
    bool alive = true;
};
