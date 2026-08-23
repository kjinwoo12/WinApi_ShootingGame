#include "OrbitMineBehavior.h"
#include "Collision.h"

namespace
{

Enemy* findMidBoss(World& world)
{
    for (Enemy& e : world.enemies)
    {
        if (e.alive && e.kind == EnemyKind::MidBoss)
            return &e;
    }
    return nullptr;
}

} // namespace

bool OrbitMineBehavior::configure(World&, RandomSource&, Enemy&) const
{
    return false;
}

KillOutcome OrbitMineBehavior::killOutcome(const World&) const
{
    return {150, 2, 1.f, true};
}

void OrbitMineBehavior::tick(EnemySystems&, World& world, RandomSource& rng, Enemy& e, float dt) const
{
    Enemy* boss = findMidBoss(world);
    if (!boss)
    {
        e.alive = false;
        return;
    }
    e.orbitAngle += 1.2f * dt;
    e.pos = boss->pos + Vec2{std::cos(e.orbitAngle) * 90.f, std::sin(e.orbitAngle) * 90.f};
    e.bank = 2;
    if (world.session.bossIntroActive())
    {
        const float t = world.session.bossIntroProgress();
        e.drawScale = clampFloat((t - 0.35f) / 0.35f, 0.f, 1.f);
    }
    else
    {
        e.drawScale = 1.f;
    }
    (void)rng;
}
