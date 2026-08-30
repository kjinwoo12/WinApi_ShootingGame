#include "MidBossEncounter.h"

void MidBossEncounter::begin(World& world, RandomSource& rng)
{
    for (Enemy& e : world.enemies)
    {
        e.alive = false;
    }
    world.bullets.clear();

    Enemy boss;
    boss.kind = EnemyKind::MidBoss;
    boss.pos = {ScreenWidth * 0.5f, -140.f};
    boss.homeX = boss.pos.x;
    boss.color = 2;
    boss.bank = 2;
    boss.drawScale = 1.4f;
    boss.radius = 36.f;
    const int sector = world.session.run.sector;
    boss.hp = boss.maxHp = 80.f + sector * 15.f;
    boss.vel = {0.f, 0.f};
    boss.patternTimer = 0.f;
    boss.patternStep = 0;
    boss.shootCooldown = 0.f;
    boss.respawnTimer = 8.f;
    world.enemies.push_back(boss);

    RunSession& run = world.session.run;
    run.midBossAlive = true;
    run.midBossHpRatio = 1.f;
    run.bossIntroDuration = 3.5f;
    run.bossIntroTimer = run.bossIntroDuration;
    world.player.invuln = (std::max)(world.player.invuln, run.bossIntroDuration);
    world.session.presentation.shake = (std::max)(world.session.presentation.shake, 0.35f);

    for (int i = 0; i < 4; ++i)
    {
        Enemy orb;
        orb.kind = EnemyKind::OrbitMine;
        orb.orbitAngle = (Pi * 2.f * static_cast<float>(i)) / 4.f;
        orb.pos = boss.pos + Vec2{std::cos(orb.orbitAngle) * 90.f, std::sin(orb.orbitAngle) * 90.f};
        orb.hp = orb.maxHp = 6.f;
        orb.radius = 16.f;
        orb.drawScale = 0.2f;
        orb.anim = rng.nextFloat(0.f, 4.f);
        world.enemies.push_back(orb);
    }
    (void)rng;
}

void MidBossEncounter::tickSession(World& world, EffectsEngine& fx, RandomSource& rng, float dt)
{
    RunSession& run = world.session.run;
    if (!run.bossIntroActive())
        return;

    run.bossIntroTimer -= dt;
    const float pulse = 0.15f + 0.1f * (0.5f + 0.5f * std::sin(run.gameTime * 14.f));
    world.session.presentation.shake = (std::max)(world.session.presentation.shake, pulse);
    if (run.bossIntroTimer <= 0.f)
    {
        run.bossIntroTimer = 0.f;
        world.session.presentation.shake = (std::max)(world.session.presentation.shake, 0.7f);
        fx.spawnHitSparks(world, rng, {ScreenWidth * 0.5f, 160.f}, false);
    }
}
