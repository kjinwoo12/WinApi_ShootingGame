#pragma once
#include "IScene.h"

struct PlayerState;

class TitleScene : public SceneBase
{
public:
    void update(SceneContext& ctx, float dt) override;
    void render(SceneContext& ctx) override;
    void onKeyDown(SceneContext& ctx, WPARAM key) override;

private:
    static void layoutDemoShip(PlayerState& player);
};
