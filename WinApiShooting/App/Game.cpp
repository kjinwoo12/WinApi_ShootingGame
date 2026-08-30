#include "Game.h"
#include "IScene.h"
#include "TitleScene.h"

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

    if (key == 'X' || key == 'x' || key == 'C' || key == 'c')
    {
        ctx.input.bombEdge = true;
    }

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
    ctx.world.session.titlePulse += dt;
    ctx.world.session.gameTime += dt;

    if (ctx.world.session.shake > 0.f)
    {
        ctx.world.session.shake = (std::max)(0.f, ctx.world.session.shake - dt * 8.f);
    }

    scene->update(ctx, dt);
    applyPendingScene();
}

void Game::render(HDC hdc)
{
    scene->render(ctx, hdc);
}

void Game::applyPendingScene()
{
    std::unique_ptr<IScene> next = scene->takeNextScene();
    if (next)
    {
        scene = std::move(next);
    }
}
