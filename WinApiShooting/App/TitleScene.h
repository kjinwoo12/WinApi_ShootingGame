#pragma once
#include "IScene.h"

class TitleScene : public SceneBase
{
public:
    void update(SceneContext& ctx, float dt) override;
    void render(SceneContext& ctx, HDC hdc) override;
    void onKeyDown(SceneContext& ctx, WPARAM key) override;
    void onKeyUp(SceneContext& ctx, WPARAM key) override;
};
