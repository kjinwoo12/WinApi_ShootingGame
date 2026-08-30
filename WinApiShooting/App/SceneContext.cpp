#include "SceneContext.h"
#include "PlayingServices.h"
#include <cassert>

SceneContext::SceneContext() = default;

SceneContext::~SceneContext() = default;

void SceneContext::startPlaying()
{
    if (!playing_)
        playing_ = std::make_unique<PlayingServices>(fx);
}

void SceneContext::stopPlaying()
{
    playing_.reset();
}

bool SceneContext::hasPlaying() const
{
    return playing_ != nullptr;
}

PlayingServices& SceneContext::playing()
{
    assert(playing_);
    return *playing_;
}

const PlayingServices& SceneContext::playing() const
{
    assert(playing_);
    return *playing_;
}
