#pragma once
#include "IScene.h"

class GameOverScene : public SceneBase
{
public:
    void update(SceneContext& ctx, float dt) override;
    void render(SceneContext& ctx) override;
    void onKeyDown(SceneContext& ctx, WPARAM key) override;
};
