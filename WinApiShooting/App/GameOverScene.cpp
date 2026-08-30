#include "GameOverScene.h"
#include "SceneContext.h"
#include "TitleScene.h"

void GameOverScene::update(SceneContext& ctx, float dt)
{
    ctx.world.session.backgroundOffset += 30.f * dt;
    ctx.fx.updateExplosions(ctx.world, ctx.assets, dt);
    ctx.fx.updateParticles(ctx.world, dt);
}

void GameOverScene::render(SceneContext& ctx, HDC hdc)
{
    ctx.renderer.draw(hdc, GameState::GameOver, ctx.world, ctx.assets, ctx.rng);
}

void GameOverScene::onKeyDown(SceneContext& ctx, WPARAM key)
{
    if (key == VK_RETURN || key == VK_SPACE)
    {
        goTo(std::make_unique<TitleScene>());
    }
}

void GameOverScene::onKeyUp(SceneContext& ctx, WPARAM key)
{
    (void)ctx;
    (void)key;
}
