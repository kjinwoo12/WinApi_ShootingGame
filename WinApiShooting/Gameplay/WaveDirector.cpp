#include "WaveDirector.h"
#include "MidBossEncounter.h"
#include "WaveCatalog.h"
#include <array>

namespace
{

using SpawnFn = void (*)(EnemySimulator& enemies, World& world, RandomSource& rng,
                         float top, float playerX);

void spawnF01(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    const float x = rng.nextFloat(160.f, ScreenWidth - 160.f);
    for (int i = 0; i < 5; ++i)
    {
        enemies.spawnEnemy(world, rng, EnemyKind::Scout, x, top - i * 48.f, 0);
    }
}

void spawnF02(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    for (int i = 0; i < 6; ++i)
    {
        const float x = 80.f + i * ((620.f - 80.f) / 5.f);
        enemies.spawnEnemy(world, rng, EnemyKind::Scout, x, top, 0);
    }
}

void spawnF03(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    const int color = (world.session.run.wave <= 3) ? 0 : 1;
    const float cx = ScreenWidth * 0.5f;
    for (int i = 0; i < 7; ++i)
    {
        const float offset = static_cast<float>(i - 3);
        const float x = cx + offset * 55.f;
        const float y = top - (3.f - std::fabs(offset)) * 36.f;
        enemies.spawnEnemy(world, rng, EnemyKind::Scout, x, y, color);
    }
}

void spawnF04(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    for (int i = 0; i < 5; ++i)
    {
        const float x = 100.f + i * 120.f;
        const float y = top - i * (0.15f * 120.f);
        enemies.spawnEnemy(world, rng, EnemyKind::Scout, x, y, -1);
    }
}

void spawnF05(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float playerX)
{
    enemies.spawnEnemy(world, rng, EnemyKind::Fighter, playerX - 70.f, top - 40.f, 1);
    enemies.spawnEnemy(world, rng, EnemyKind::Fighter, playerX + 70.f, top - 80.f, 1);
}

void spawnF06(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    for (int i = 0; i < 4; ++i)
    {
        enemies.spawnEnemy(world, rng, EnemyKind::MineSeeker,
                           rng.nextFloat(50.f, ScreenWidth - 50.f),
                           top - rng.nextFloat(0.f, 160.f), -1);
    }
}

void spawnF07(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    enemies.spawnEnemy(world, rng, EnemyKind::MineSentry, 150.f, top - 20.f, -1);
    enemies.spawnEnemy(world, rng, EnemyKind::MineSentry, 350.f, top - 40.f, -1);
    enemies.spawnEnemy(world, rng, EnemyKind::MineSentry, 550.f, top - 20.f, -1);
}

void spawnF08(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    enemies.spawnEnemy(world, rng, EnemyKind::SawPatrol, 120.f, top - 30.f, -1);
    world.enemies.back().vel.x = 90.f;
    enemies.spawnEnemy(world, rng, EnemyKind::SawPatrol, ScreenWidth - 120.f, top - 110.f, -1);
    world.enemies.back().vel.x = -90.f;
}

void spawnF09(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    for (int i = 0; i < 8; ++i)
    {
        enemies.spawnEnemy(world, rng, EnemyKind::Scout,
                           rng.nextFloat(60.f, ScreenWidth - 60.f),
                           top - i * 28.f, 2);
    }
    enemies.spawnEnemy(world, rng, EnemyKind::Fighter, ScreenWidth * 0.5f, top - 220.f, 2);
}

void spawnF10(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float playerX)
{
    for (int i = -1; i <= 1; ++i)
    {
        enemies.spawnEnemy(world, rng, EnemyKind::MineBurst,
                           clampFloat(playerX + i * 90.f, 60.f, ScreenWidth - 60.f),
                           top - 40.f - std::fabs(static_cast<float>(i)) * 50.f, -1);
    }
}

void spawnF11(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    for (int i = 0; i < 6; ++i)
    {
        const float x = 80.f + i * ((620.f - 80.f) / 5.f);
        enemies.spawnEnemy(world, rng, EnemyKind::Scout, x, top, 0);
    }
    enemies.spawnEnemy(world, rng, EnemyKind::Fighter, 200.f, top - 120.f, 1);
    enemies.spawnEnemy(world, rng, EnemyKind::Fighter, 500.f, top - 140.f, 1);
}

void spawnF12(EnemySimulator& enemies, World& world, RandomSource& rng, float top, float)
{
    enemies.spawnEnemy(world, rng, EnemyKind::SawChase, 100.f, top - 20.f, -1);
    enemies.spawnEnemy(world, rng, EnemyKind::SawChase, ScreenWidth - 100.f, top - 80.f, -1);
}

// 인덱스 = FormationId - 1 (F01Column=1).
static constexpr std::array<SpawnFn, 12> kFormations = {
    spawnF01,
    spawnF02,
    spawnF03,
    spawnF04,
    spawnF05,
    spawnF06,
    spawnF07,
    spawnF08,
    spawnF09,
    spawnF10,
    spawnF11,
    spawnF12,
};

} // namespace

WaveDirector::WaveDirector(EnemySimulator& enemySim)
    : enemies(enemySim) {}

void WaveDirector::spawnFormation(World& world, RandomSource& rng, FormationId id)
{
    const int i = static_cast<int>(id) - 1;
    if (i < 0 || i >= static_cast<int>(kFormations.size()) || !kFormations[static_cast<size_t>(i)])
    {
        return;
    }
    kFormations[static_cast<size_t>(i)](enemies, world, rng, -60.f, world.player.pos.x);
}

void WaveDirector::spawnWave(World& world, RandomSource& rng)
{
    ++world.session.run.wave;
    const int wave = world.session.run.wave;
    world.session.run.sector = ((wave - 1) / 3) + 1;

    if (WaveCatalog::isMidBossWave(wave, world.session.run.sector))
    {
        MidBossEncounter::begin(world, rng);
        world.session.run.waveTimer = 2.5f;
        return;
    }

    const WavePlan plan = WaveCatalog::planForWave(wave);
    for (int i = 0; i < plan.count; ++i)
    {
        spawnFormation(world, rng, plan.forms[i]);
    }
    if (plan.bonusFighter)
    {
        enemies.spawnEnemy(world, rng, EnemyKind::Fighter, ScreenWidth * 0.5f, -200.f, 1);
    }

    world.session.run.waveTimer = 2.5f;
}

void WaveDirector::trySpawn(World& world, RandomSource& rng, float dt)
{
    RunSession& run = world.session.run;

    if (run.sectorClearTimer > 0.f)
    {
        run.sectorClearTimer -= dt;
        if (run.sectorClearTimer <= 0.f)
        {
            spawnWave(world, rng);
        }
        return;
    }

    if (run.midBossAlive)
    {
        return;
    }

    run.waveTimer -= dt;
    if (run.waveTimer > 0.f || !world.enemies.empty())
    {
        return;
    }

    if (run.wave > 0 && run.wave % 3 == 0)
    {
        run.sectorClearTimer = 2.0f;
        if (run.sectorNoHit)
        {
            run.score += 2000;
            world.player.bombs = clampInt(world.player.bombs + 1, 0, 5);
        }
        run.sectorNoHit = true;
        return;
    }

    spawnWave(world, rng);
}
