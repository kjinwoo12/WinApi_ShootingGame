#include "TitleScene.h"
#include "PlayerState.h"
#include "PlayingScene.h"
#include "SceneContext.h"
#include "TitleOverlay.h"
#include "WorldView.h"

void TitleScene::layoutDemoShip(PlayerState& player)
{
    player.pos = {ScreenWidth * 0.5f, ScreenHeight * 0.80f};
    player.vel = {0.f, 0.f};
    player.lives = 1;
    player.invuln = 0.f;
    player.focusing = false;
}

void TitleScene::update(SceneContext& ctx, float dt)
{
    PresentationSession& pres = ctx.world.session.presentation;
    pres.titlePulse += dt;
    pres.advanceScroll(40.f * dt, ctx.assets.backgroundHeight());
    layoutDemoShip(ctx.world.player);
    ctx.world.player.exhaustAnim += dt * 12.f;
    ctx.fx.updateExplosions(ctx.world, dt);
    ctx.fx.updateParticles(ctx.world, dt);
}

void TitleScene::render(SceneContext& ctx)
{
    const WorldView worldView;
    const TitleOverlay overlay;

    worldView.render(ctx.renderer.worldGraphics(), ctx.world, ctx.assets);
    overlay.render(ctx.renderer.endWorldLayer(), ctx.world, ctx.assets);
}

void TitleScene::onKeyDown(SceneContext& ctx, WPARAM key)
{
    if (key == VK_RETURN || key == VK_SPACE)
    {
        ctx.world.resetRun();
        ctx.startPlaying();
        goTo(std::make_unique<PlayingScene>());
    }
}
