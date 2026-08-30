#include "WorldView.h"
#include "WorldObjects.h"

void WorldView::render(Gdiplus::Graphics& g, const World& world, const Assets& assets) const
{
    for (const Particle& particle : world.particles)
    {
        if (particle.alive)
            ParticleObject(particle).render(g);
    }

    for (const Enemy& enemy : world.enemies)
    {
        if (enemy.alive)
            EnemyObject(enemy).render(g, assets);
    }

    for (const PowerUp& powerUp : world.powerUps)
    {
        if (powerUp.alive)
            PowerUpObject(powerUp).render(g, assets);
    }

    for (const Bullet& bullet : world.bullets)
    {
        if (bullet.alive)
            BulletObject(bullet).render(g, assets);
    }

    for (const Explosion& explosion : world.explosions)
    {
        if (explosion.alive)
            ExplosionObject(explosion).render(g, assets);
    }

    PlayerObject(world.player).render(g, assets);
}
