#include "IScene.h"

float IScene::screenShake(const SceneContext&) const
{
    return 0.f;
}

void SceneBase::goTo(std::unique_ptr<IScene> next)
{
    nextScene = std::move(next);
}

std::unique_ptr<IScene> SceneBase::takeNextScene()
{
    return std::move(nextScene);
}
