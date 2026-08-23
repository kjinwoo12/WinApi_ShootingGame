#include "EnemySimulator.h"
#include "Collision.h"
#include "EnemyBehaviors.h"

EnemySimulator::EnemySimulator(BulletSystem& bulletSys, EffectsEngine& effects)
    : bullets(bulletSys), fx(effects) {}

int EnemySimulator::pickFactionColor(RandomSource& rng, int wave) const
{
    const int sector = (wave <= 0) ? 1 : ((wave - 1) / 3) + 1;
    const float roll = rng.nextFloat(0.f, 1.f);
    if (sector <= 1)
        return (roll < 0.80f) ? 0 : 1;
    if (sector == 2)
    {
        if (roll < 0.40f)
            return 0;
        if (roll < 0.90f)
            return 1;
        return 2;
    }
    if (sector == 3)
    {
        if (roll < 0.25f)
            return 0;
        if (roll < 0.75f)
            return 1;
        return 2;
    }
    if (sector == 4)
    {
        if (roll < 0.20f)
            return 0;
        if (roll < 0.45f)
            return 1;
        return 2;
    }
    if (roll < 0.33f)
        return 0;
    if (roll < 0.66f)
        return 1;
    return 2;
}

void EnemySimulator::spawnEnemy(World& world, RandomSource& rng, EnemyKind kind,
                                float x, float y, int color)
{
    Enemy e;
    e.kind = kind;
    e.pos = {x, y};
    e.homeX = x;
    e.color = (color >= 0 && color <= 2) ? color : pickFactionColor(rng, world.session.wave);
    e.phase = rng.nextFloat(0.f, Pi * 2.f);
    e.anim = rng.nextFloat(0.f, 8.f);

    if (!EnemyBehaviors::at(kind).configure(world, rng, e))
        return;
    world.enemies.push_back(e);
}

void EnemySimulator::spawnMidBoss(World& world, RandomSource& rng)
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
    const int sector = world.session.sector;
    boss.hp = boss.maxHp = 80.f + sector * 15.f;
    boss.vel = {0.f, 0.f};
    boss.patternTimer = 0.f;
    boss.patternStep = 0;
    boss.shootCooldown = 0.f;
    boss.respawnTimer = 8.f;
    world.enemies.push_back(boss);
    world.session.midBossAlive = true;
    world.session.bossIntroDuration = 3.5f;
    world.session.bossIntroTimer = world.session.bossIntroDuration;
    world.player.invuln = (std::max)(world.player.invuln, world.session.bossIntroDuration);
    world.session.shake = (std::max)(world.session.shake, 0.35f);

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
}

void EnemySimulator::update(World& world, RandomSource& rng, float dt)
{
    EnemySystems sys{bullets, fx};

    for (Enemy& e : world.enemies)
    {
        if (!e.alive)
            continue;
        const IEnemyBehavior& behavior = EnemyBehaviors::at(e.kind);
        e.anim += dt * (behavior.isMineVisual() ? 12.f : 6.f);
        e.phase += dt;
        behavior.tick(sys, world, rng, e, dt);
        e.bank = bankFromVelocity(e.vel.x);
        if (behavior.cullOffscreen())
        {
            if (e.pos.y > ScreenHeight + 80.f || e.pos.x < -100.f || e.pos.x > ScreenWidth + 100.f)
            {
                e.alive = false;
            }
        }
    }

    world.enemies.erase(
        std::remove_if(world.enemies.begin(), world.enemies.end(),
                       [](const Enemy& e)
                       { return !e.alive; }),
        world.enemies.end());
}
