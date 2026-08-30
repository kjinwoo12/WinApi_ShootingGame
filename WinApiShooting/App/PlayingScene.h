#pragma once
#include "IScene.h"

class PlayingScene : public SceneBase
{
public:
    void update(SceneContext& ctx, float dt) override;
    void render(SceneContext& ctx) override;
    float screenShake(const SceneContext& ctx) const override;
    void onKeyDown(SceneContext& ctx, WPARAM key) override;
};
