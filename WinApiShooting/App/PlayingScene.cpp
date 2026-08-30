#include "PlayingScene.h"
#include "GameOverScene.h"
#include "PlayingHudView.h"
#include "PlayingSession.h"
#include "SceneContext.h"
#include "WorldView.h"

void PlayingScene::update(SceneContext& ctx, float dt)
{
    if (!ctx.hasPlaying())
        return;

    const float bgHeight = ctx.assets.backgroundHeight();
    if (PlayingSession::tick(ctx.world, ctx.input, ctx.rng, ctx.fx, ctx.playing(), bgHeight, dt))
    {
        ctx.stopPlaying();
        goTo(std::make_unique<GameOverScene>());
    }
}

float PlayingScene::screenShake(const SceneContext& ctx) const
{
    return ctx.world.session.presentation.shake;
}

void PlayingScene::render(SceneContext& ctx)
{
    Renderer& r = ctx.renderer;
    const World& world = ctx.world;
    const Assets& assets = ctx.assets;
    const WorldView worldView;
    const PlayingHudView hud;

    worldView.render(r.worldGraphics(), world, assets);

    if (ctx.hasPlaying())
        hud.render(r.endWorldLayer(), world, assets);
    else
        r.endWorldLayer();
}

void PlayingScene::onKeyDown(SceneContext& ctx, WPARAM key)
{
    if (key == 'X' || key == 'x' || key == 'C' || key == 'c')
        ctx.input.bombEdge = true;
}
