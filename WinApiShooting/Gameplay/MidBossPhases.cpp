#include "MidBossPhases.h"
#include "Collision.h"

void MidBossPhases::tickIntro(Enemy& e, const World& world)
{
    const float t = world.session.run.bossIntroProgress();
    const float descend = clampFloat(t / 0.55f, 0.f, 1.f);
    const float ease = descend * descend * (3.f - 2.f * descend);
    e.pos.x = ScreenWidth * 0.5f;
    e.pos.y = lerp(-140.f, 150.f, ease);
    e.vel = {0.f, 0.f};
    e.bank = 2;
    e.drawScale = lerp(1.4f, 2.2f, ease);
}

void MidBossPhases::tickPatrol(Enemy& e, float dt)
{
    e.patternTimer += dt;
    e.shootCooldown -= dt;
    if (e.vel.x == 0.f)
        e.vel.x = 40.f;
    e.drawScale = 2.2f;

    e.pos.x += e.vel.x * dt;
    if (e.pos.x < 140.f)
    {
        e.pos.x = 140.f;
        e.vel.x = std::fabs(e.vel.x);
    }
    else if (e.pos.x > 560.f)
    {
        e.pos.x = 560.f;
        e.vel.x = -std::fabs(e.vel.x);
    }
    e.pos.y = lerp(e.pos.y, 150.f, clampFloat(dt * 2.f, 0.f, 1.f));
}

void MidBossPhases::tickOrbitRespawn(World& world, RandomSource& rng, Enemy& e, float dt)
{
    int orbCount = 0;
    for (const Enemy& o : world.enemies)
    {
        if (o.alive && o.kind == EnemyKind::OrbitMine)
            ++orbCount;
    }
    if (orbCount < 4)
    {
        e.respawnTimer -= dt;
        if (e.respawnTimer <= 0.f)
        {
            Enemy orb;
            orb.kind = EnemyKind::OrbitMine;
            orb.orbitAngle = rng.nextFloat(0.f, Pi * 2.f);
            orb.pos = e.pos + Vec2{std::cos(orb.orbitAngle) * 90.f, std::sin(orb.orbitAngle) * 90.f};
            orb.hp = orb.maxHp = 6.f;
            orb.radius = 16.f;
            orb.drawScale = 1.f;
            world.enemies.push_back(orb);
            e.respawnTimer = 8.f;
        }
    }
    else
    {
        e.respawnTimer = 8.f;
    }
}

void MidBossPhases::tickAttack(EnemySystems& sys, World& world, RandomSource& rng, Enemy& e,
                               const Vec2& playerPos)
{
    const float cycle = std::fmod(e.patternTimer, 20.f);
    if (cycle < 14.f)
    {
        e.patternStep = 0;
    }

    if (cycle < 4.f)
    {
        if (e.shootCooldown <= 0.f)
        {
            sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Plasma,
                              e.pos + Vec2{0.f, 40.f}, {0.f, 360.f}, 1);
            e.shootCooldown = 0.2f;
        }
    }
    else if (cycle < 8.f)
    {
        if (e.shootCooldown <= 0.f)
        {
            Vec2 dir = playerPos - e.pos;
            if (length(dir) < 0.1f)
                dir = {0.f, 1.f};
            else
                dir = normalize(dir);
            const float baseAng = std::atan2(dir.y, dir.x);
            const float speed = 340.f;
            for (int i = -1; i <= 1; ++i)
            {
                const float ang = baseAng + static_cast<float>(i) * (18.f * Pi / 180.f);
                sys.bullets.spawn(world, BulletOwner::Enemy, WeaponLevel::Plasma,
                                  e.pos + Vec2{0.f, 30.f},
                                  {std::cos(ang) * speed, std::sin(ang) * speed}, 1);
            }
            e.shootCooldown = 0.9f;
        }
    }
    else if (cycle >= 14.f && e.patternStep == 0)
    {
        e.patternStep = 1;
        for (Enemy& orb : world.enemies)
        {
            if (!orb.alive || orb.kind != EnemyKind::OrbitMine)
                continue;
            orb.kind = EnemyKind::SawChase;
            orb.drawScale = 1.f;
            orb.radius = 18.f;
            orb.hp = orb.maxHp = 5.f;
            orb.vel = {rng.nextFloat(-60.f, 60.f), 80.f};
            break;
        }
    }
}
