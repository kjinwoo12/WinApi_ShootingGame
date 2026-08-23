#pragma once
#include "Entities.h"
#include "UiSprites.h"
#include "WorldSprites.h"

class Assets
{
public:
    bool load(HWND ownerWindow);

    const Sprite& playerSprite(int bank, bool rage) const;
    const Sprite& playerShadowSprite(int bank) const;
    const Sprite& enemySprite(const Enemy& enemy) const;
    const Sprite& enemyShadowSprite(const Enemy& enemy) const;
    const Sprite& bulletSprite(const Bullet& bullet) const;
    const Sprite& explosionSprite(int type, int frame) const;

    WorldSprites world;
    UiSprites ui;

private:
    bool resolveRoot(HWND ownerWindow);

    std::wstring root;
};
