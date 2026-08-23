#include "Game.h"
#include "PlayingSession.h"

Game::Game()
    : powerUps(fx), weapon(bullets, fx), combat(fx, bullets), player(weapon, combat), enemies(bullets, fx), waves(enemies) {}

bool Game::init(HWND hwnd)
{
    window = hwnd;
    if (!assets.load(window))
        return false;
    if (!renderer.init())
        return false;
    world.reserveDefaults();
    state = GameState::Title;
    return true;
}

void Game::shutdown()
{
    renderer.shutdown();
}

void Game::onKeyDown(WPARAM key)
{
    input.setKey(key, true);

    if (key == 'X' || key == 'x' || key == 'C' || key == 'c')
    {
        input.bombEdge = true;
    }

    if (key == VK_ESCAPE)
    {
        PostMessageW(window, WM_CLOSE, 0, 0);
        return;
    }

    if (state == GameState::Title && (key == VK_RETURN || key == VK_SPACE))
    {
        world.resetRun();
        state = GameState::Playing;
        return;
    }

    if (state == GameState::GameOver && (key == VK_RETURN || key == VK_SPACE))
    {
        state = GameState::Title;
    }
}

void Game::onKeyUp(WPARAM key)
{
    input.setKey(key, false);
}

void Game::update(float dt)
{
    world.session.titlePulse += dt;
    world.session.gameTime += dt;

    if (world.session.shake > 0.f)
    {
        world.session.shake = (std::max)(0.f, world.session.shake - dt * 8.f);
    }

    switch (state)
    {
    case GameState::Title:
        updateTitle(dt);
        break;
    case GameState::Playing:
        updatePlaying(dt);
        break;
    case GameState::GameOver:
        updateGameOver(dt);
        break;
    }
}

void Game::updateTitle(float dt)
{
    world.session.backgroundOffset += 40.f * dt;
    if (world.session.backgroundOffset >= assets.world.background.height())
    {
        world.session.backgroundOffset -= static_cast<float>(assets.world.background.height());
    }
    world.player.exhaustAnim += dt * 12.f;
    fx.updateExplosions(world, assets, dt);
    fx.updateParticles(world, dt);
}

void Game::updateGameOver(float dt)
{
    world.session.backgroundOffset += 30.f * dt;
    fx.updateExplosions(world, assets, dt);
    fx.updateParticles(world, dt);
}

void Game::updatePlaying(float dt)
{
    PlayingSession::tickTimers(world, fx, rng, static_cast<float>(assets.world.background.height()), dt);

    player.update(world, input, rng, dt);
    enemies.update(world, rng, dt);
    bullets.update(world, dt);
    fx.updateExplosions(world, assets, dt);
    powerUps.update(world, rng, dt);
    fx.updateParticles(world, dt);
    combat.handleCollisions(world, rng);
    waves.trySpawn(world, rng, dt);

    if (PlayingSession::checkPlayerDeath(world, fx, rng))
    {
        state = GameState::GameOver;
    }
}

void Game::render(HDC hdc)
{
    renderer.draw(hdc, state, world, assets, rng);
}
