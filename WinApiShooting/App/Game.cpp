#include "Game.h"
#include "TitleScene.h"
#include "Renderer.h"

Game::Game() = default;

bool Game::init(HWND hwnd)
{
    ctx.window = hwnd;
    if (!ctx.assets.load(hwnd))
        return false;
    if (!ctx.renderer.init())
        return false;
    ctx.world.reserveDefaults();
    scene = std::make_unique<TitleScene>();
    return true;
}

void Game::shutdown()
{
    ctx.renderer.shutdown();
}

void Game::onKeyDown(WPARAM key)
{
    ctx.input.setKey(key, true);

    if (key == VK_ESCAPE)
    {
        PostMessageW(ctx.window, WM_CLOSE, 0, 0);
        return;
    }

    scene->onKeyDown(ctx, key);
}

void Game::onKeyUp(WPARAM key)
{
    ctx.input.setKey(key, false);
    scene->onKeyUp(ctx, key);
}

void Game::update(float dt)
{
    scene->update(ctx, dt);
    applyPendingScene();
}

void Game::render(HDC hdc)
{
    Renderer& r = ctx.renderer;
    r.beginFrame(ctx.world, ctx.assets, ctx.rng, scene->screenShake(ctx));
    scene->render(ctx);
    r.present(hdc);
}

void Game::applyPendingScene()
{
    std::unique_ptr<IScene> next = scene->takeNextScene();
    if (next)
    {
        scene = std::move(next);
    }
}
