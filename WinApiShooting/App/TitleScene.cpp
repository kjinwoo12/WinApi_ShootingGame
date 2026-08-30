#include "TitleScene.h"
#include "PlayingScene.h"
#include "SceneContext.h"

void TitleScene::update(SceneContext& ctx, float dt)
{
    ctx.world.session.backgroundOffset += 40.f * dt;
    if (ctx.world.session.backgroundOffset >= ctx.assets.world.background.height())
    {
        ctx.world.session.backgroundOffset -= static_cast<float>(ctx.assets.world.background.height());
    }
    ctx.world.player.exhaustAnim += dt * 12.f;
    ctx.fx.updateExplosions(ctx.world, ctx.assets, dt);
    ctx.fx.updateParticles(ctx.world, dt);
}

void TitleScene::render(SceneContext& ctx, HDC hdc)
{
    ctx.renderer.draw(hdc, GameState::Title, ctx.world, ctx.assets, ctx.rng);
}

void TitleScene::onKeyDown(SceneContext& ctx, WPARAM key)
{
    if (key == VK_RETURN || key == VK_SPACE)
    {
        ctx.world.resetRun();
        goTo(std::make_unique<PlayingScene>());
    }
}

void TitleScene::onKeyUp(SceneContext& ctx, WPARAM key)
{
    (void)ctx;
    (void)key;
}
