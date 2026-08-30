#pragma once
#include "IScene.h"
#include "SceneContext.h"
#include <memory>

class Game
{
public:
    Game();
    ~Game() = default;

    bool init(HWND hwnd);
    void shutdown();
    void update(float dt);
    void render(HDC hdc);
    void onKeyDown(WPARAM key);
    void onKeyUp(WPARAM key);

private:
    void applyPendingScene();

    SceneContext ctx;
    std::unique_ptr<IScene> scene;
};
