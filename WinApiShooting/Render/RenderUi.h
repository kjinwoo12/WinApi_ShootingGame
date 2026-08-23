#pragma once
#include "Assets.h"
#include "World.h"

namespace RenderUi
{
void drawPowerUp(Gdiplus::Graphics& g, const PowerUp& powerUp, const Assets& assets);
void drawBossIntro(Gdiplus::Graphics& g, const World& world, const Assets& assets);
void drawHud(Gdiplus::Graphics& g, const World& world, const Assets& assets);
void drawTitle(Gdiplus::Graphics& g, const World& world, const Assets& assets);
void drawGameOver(Gdiplus::Graphics& g, const World& world, const Assets& assets);
} // namespace RenderUi
