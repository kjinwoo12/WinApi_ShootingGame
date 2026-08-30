#include "GameOverScene.h"
#include "GameOverOverlay.h"
#include "SceneContext.h"
#include "TitleScene.h"
#include "WorldView.h"

void GameOverScene::update(SceneContext& ctx, float dt)
{
    ctx.world.session.presentation.advanceScroll(30.f * dt, ctx.assets.backgroundHeight());
    ctx.fx.updateExplosions(ctx.world, dt);
    ctx.fx.updateParticles(ctx.world, dt);
}

void GameOverScene::render(SceneContext& ctx)
{
    const WorldView worldView;
    const GameOverOverlay overlay;

    worldView.render(ctx.renderer.worldGraphics(), ctx.world, ctx.assets);
    overlay.render(ctx.renderer.endWorldLayer(), ctx.world, ctx.assets);
}

void GameOverScene::onKeyDown(SceneContext& ctx, WPARAM key)
{
    if (key == VK_RETURN || key == VK_SPACE)
        goTo(std::make_unique<TitleScene>());
}
