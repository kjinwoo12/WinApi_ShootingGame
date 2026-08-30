#include "PlayingScene.h"
#include "GameOverScene.h"
#include "PlayingSession.h"
#include "SceneContext.h"

void PlayingScene::update(SceneContext& ctx, float dt)
{
    PlayingSession::tickTimers(ctx.world, ctx.fx, ctx.rng,
                               static_cast<float>(ctx.assets.world.background.height()), dt);

    ctx.player.update(ctx.world, ctx.input, ctx.rng, dt);
    ctx.enemies.update(ctx.world, ctx.rng, dt);
    ctx.bullets.update(ctx.world, dt);
    ctx.fx.updateExplosions(ctx.world, ctx.assets, dt);
    ctx.powerUps.update(ctx.world, ctx.rng, dt);
    ctx.fx.updateParticles(ctx.world, dt);
    ctx.combat.handleCollisions(ctx.world, ctx.rng);
    ctx.waves.trySpawn(ctx.world, ctx.rng, dt);

    if (PlayingSession::checkPlayerDeath(ctx.world, ctx.fx, ctx.rng))
    {
        goTo(std::make_unique<GameOverScene>());
    }
}

void PlayingScene::render(SceneContext& ctx, HDC hdc)
{
    ctx.renderer.draw(hdc, GameState::Playing, ctx.world, ctx.assets, ctx.rng);
}

void PlayingScene::onKeyDown(SceneContext& ctx, WPARAM key)
{
    (void)ctx;
    (void)key;
}

void PlayingScene::onKeyUp(SceneContext& ctx, WPARAM key)
{
    (void)ctx;
    (void)key;
}
