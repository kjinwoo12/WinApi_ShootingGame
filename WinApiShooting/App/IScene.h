#pragma once
#include "Common.h"
#include <memory>

struct SceneContext;

class IScene
{
public:
    virtual ~IScene() = default;

    virtual void update(SceneContext& ctx, float dt) = 0;
    virtual void render(SceneContext& ctx, HDC hdc) = 0;
    virtual void onKeyDown(SceneContext& ctx, WPARAM key) = 0;
    virtual void onKeyUp(SceneContext& ctx, WPARAM key) = 0;
    virtual std::unique_ptr<IScene> takeNextScene() = 0;
};

class SceneBase : public IScene
{
public:
    std::unique_ptr<IScene> takeNextScene() override;

protected:
    void goTo(std::unique_ptr<IScene> next);

private:
    std::unique_ptr<IScene> nextScene;
};
