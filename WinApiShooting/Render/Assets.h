#pragma once
#include "Entities.h"
#include "PlayerState.h"
#include "PowerUp.h"
#include "Sprite.h"
#include "UiSprites.h"
#include "WorldSprites.h"

struct BulletDrawParams
{
    float scale = 1.f;
    float rotationDeg = 0.f;
};

class Assets
{
public:
    bool load(HWND ownerWindow);

    float backgroundHeight() const;
    int exhaustFrameCount() const;

    const Sprite& backgroundSprite() const;
    const Sprite& playerSprite(int bank, bool rage) const;
    const Sprite& playerShadowSprite(int bank) const;
    const Sprite& exhaustSprite(int frame) const;
    const Sprite& enemySprite(const Enemy& enemy) const;
    const Sprite& enemyShadowSprite(const Enemy& enemy) const;
    const Sprite& bulletSprite(const Bullet& bullet) const;
    BulletDrawParams bulletDrawParams(const Bullet& bullet) const;
    const Sprite& explosionSprite(int type, int frame) const;
    const Sprite& powerUpFrame() const;
    const Sprite& hudWeaponIcon(WeaponLevel weapon) const;
    const Sprite& hudLifeShip() const;
    const Sprite& hudLifeSlot() const;
    const Sprite& hudBossTrack() const;
    const Sprite& hudPanel() const;
    const Sprite& hudSectorBanner() const;
    const Sprite& titlePromo() const;
    const Sprite& titleStrip() const;
    const Sprite& titleStartButton() const;
    const Sprite& titleHighScoreStrip() const;
    const Sprite& resultPanel() const;

private:
    bool resolveRoot(HWND ownerWindow);

    std::wstring root;
    WorldSprites world_;
    UiSprites ui_;
};
