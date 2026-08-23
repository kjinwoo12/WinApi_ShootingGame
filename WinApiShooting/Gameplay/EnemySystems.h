#pragma once
#include "BulletSystem.h"
#include "EffectsEngine.h"

// Behavior가 쓰는 포트 — 탄·이펙트만. 플레이어 무기/폭탄 없음.
struct EnemySystems
{
    BulletSystem& bullets;
    EffectsEngine& fx;
};
