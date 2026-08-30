#pragma once
#include "Assets.h"
#include "World.h"

class PlayingHudView
{
public:
    void render(Gdiplus::Graphics& g, const World& world, const Assets& assets) const;

private:
    void renderDock(Gdiplus::Graphics& g, const World& world, const Assets& assets) const;
    void renderBossHp(Gdiplus::Graphics& g, const World& world, const Assets& assets) const;
    void renderBossIntro(Gdiplus::Graphics& g, const World& world, const Assets& assets) const;
    void renderBombFlash(Gdiplus::Graphics& g, const World& world) const;
};
