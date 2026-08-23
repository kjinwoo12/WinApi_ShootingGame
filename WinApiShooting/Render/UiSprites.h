#pragma once
#include "Sprite.h"
#include <string>

class UiSprites
{
public:
    bool load(const std::wstring& spaceRageRoot);

    Sprite mainHud;
    Sprite mainTitle;
    Sprite mainResult;
    Sprite titleStrip;
    Sprite hiStrip;
    Sprite sliderTrack;
    Sprite sliderKnob;
    Sprite btnStart;
    Sprite btnPlate;
    Sprite btnBanner;
    Sprite hexFrame;
    Sprite lifeSlot;
};
