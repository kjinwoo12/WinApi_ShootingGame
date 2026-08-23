#pragma once

enum class EnemyKind
{
    Scout,
    Fighter,
    MineSeeker,
    MineSentry,
    MineBurst,
    SawPatrol,
    SawChase,
    MidBoss,
    OrbitMine
};

inline bool isMineKind(EnemyKind kind)
{
    return kind == EnemyKind::MineSeeker || kind == EnemyKind::MineSentry || kind == EnemyKind::MineBurst || kind == EnemyKind::SawPatrol || kind == EnemyKind::SawChase || kind == EnemyKind::OrbitMine;
}
