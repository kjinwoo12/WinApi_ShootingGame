#include "Combat.h"
#include "Collision.h"
#include "EnemyBehaviors.h"
#include "EnemySystems.h"

Combat::Combat(EffectsEngine& effects, BulletSystem& bulletSys)
    : fx(effects), bullets(bulletSys), graze(effects) {}

void Combat::detonateBomb(World& world, RandomSource& rng)
{
    PlayerState& player = world.player;
    SessionState& session = world.session;
    if (player.bombs <= 0 || player.bombing() || player.lives <= 0)
        return;

    player.bombs--;
    session.bombsUsed++;
    player.bombTimer = 0.55f;
    player.invuln = (std::max)(player.invuln, 0.80f);
    session.bombFlash = 0.25f;
    session.shake = (std::max)(session.shake, 0.55f);
    fx.spawnExplosion(world, rng, player.pos, 0, 1.8f);

    int converted = 0;
    for (Bullet& b : world.bullets)
    {
        if (!b.alive || b.owner != BulletOwner::Enemy)
            continue;
        b.alive = false;
        if (converted < 48)
        {
            graze.apply(world, rng, b.pos);
            ++converted;
            Particle spark;
            spark.pos = b.pos;
            spark.vel = {rng.nextFloat(-30.f, 30.f), rng.nextFloat(-30.f, 30.f)};
            spark.life = spark.maxLife = 0.12f;
            spark.size = 2.f;
            spark.color = Gdiplus::Color(220, 255, 255, 200);
            world.particles.push_back(spark);
        }
    }

    constexpr float blastR = 90.f;
    for (Enemy& e : world.enemies)
    {
        if (!e.alive)
            continue;
        if (length(e.pos - player.pos) > blastR)
            continue;
        const IEnemyBehavior& behavior = EnemyBehaviors::at(e.kind);
        e.hp -= behavior.bombDamage();
        fx.spawnHitSparks(world, rng, e.pos, false);
        if (e.hp <= 0.f)
        {
            e.alive = false;
            applyEnemyKill(world, rng, e);
        }
    }
}

void Combat::applyEnemyKill(World& world, RandomSource& rng, Enemy& e)
{
    PlayerState& player = world.player;
    SessionState& session = world.session;
    const IEnemyBehavior& behavior = EnemyBehaviors::at(e.kind);
    EnemySystems sys{bullets, fx};
    const KillOutcome outcome = behavior.killOutcome(world);

    behavior.onKilled(sys, world, rng, e);

    session.combo++;
    session.comboTimer = 2.2f;
    session.score += outcome.baseScore * (1 + session.combo / 5) + session.wave * 10;
    if (!player.raging())
    {
        player.rageGauge = clampFloat(player.rageGauge + 2.f, 0.f, 100.f);
    }
    player.weaponKills++;
    if (player.weapon == WeaponLevel::Vulcan && player.weaponKills >= 20)
    {
        player.weapon = WeaponLevel::Plasma;
        player.weaponKills = 0;
    }
    else if (player.weapon == WeaponLevel::Plasma && player.weaponKills >= 30)
    {
        player.weapon = WeaponLevel::Proton;
        player.weaponKills = 0;
    }
    fx.spawnExplosion(world, rng, e.pos, outcome.boomType, outcome.boomScale);
    if (outcome.spawnRandomPowerUp)
    {
        fx.spawnPowerUp(world, rng, e.pos);
    }
    session.shake = (std::max)(session.shake, 0.25f);
}

void Combat::damagePlayer(World& world, RandomSource& rng)
{
    PlayerState& player = world.player;
    SessionState& session = world.session;
    if (player.invuln > 0.f)
        return;
    player.lives--;
    session.combo = 0;
    session.sectorNoHit = false;
    player.hurtFlash = 0.45f;
    player.invuln = 2.0f;
    player.rageGauge = 0.f;
    player.rageTimer = 0.f;
    session.shake = 0.8f;
    fx.spawnExplosion(world, rng, player.pos, 0, 1.3f);
    fx.spawnHitSparks(world, rng, player.pos, true);
    if (player.weapon == WeaponLevel::Proton)
        player.weapon = WeaponLevel::Plasma;
    else if (player.weapon == WeaponLevel::Plasma)
        player.weapon = WeaponLevel::Vulcan;
}

void Combat::handleCollisions(World& world, RandomSource& rng)
{
    PlayerState& player = world.player;
    SessionState& session = world.session;
    const bool intro = session.bossIntroActive();

    graze.process(world, rng);

    for (Bullet& b : world.bullets)
    {
        if (!b.alive || b.owner != BulletOwner::Player)
            continue;
        for (Enemy& e : world.enemies)
        {
            if (!e.alive)
                continue;
            const IEnemyBehavior& behavior = EnemyBehaviors::at(e.kind);
            if (intro && behavior.invulnDuringBossIntro())
                continue;
            const float er = e.radius * e.drawScale;
            if (!circlesOverlap(b.pos, b.radius, e.pos, er))
                continue;

            e.hp -= static_cast<float>(b.damage);
            b.alive = false;
            fx.spawnHitSparks(world, rng, b.pos, false);
            if (e.hp <= 0.f)
            {
                e.alive = false;
                applyEnemyKill(world, rng, e);
            }
            break;
        }
    }

    if (player.invuln <= 0.f && player.lives > 0)
    {
        for (Bullet& b : world.bullets)
        {
            if (!b.alive || b.owner != BulletOwner::Enemy)
                continue;
            if (circlesOverlap(b.pos, b.radius, player.pos, player.radius))
            {
                b.alive = false;
                damagePlayer(world, rng);
                break;
            }
        }

        for (Enemy& e : world.enemies)
        {
            if (!e.alive)
                continue;
            const IEnemyBehavior& behavior = EnemyBehaviors::at(e.kind);
            if (intro && behavior.invulnDuringBossIntro())
                continue;
            const float er = e.radius * e.drawScale;
            if (circlesOverlap(e.pos, er, player.pos, player.radius))
            {
                if (behavior.diesOnPlayerContact())
                {
                    e.alive = false;
                }
                fx.spawnExplosion(world, rng, e.pos, 2, 1.2f);
                damagePlayer(world, rng);
                break;
            }
        }
    }
}
