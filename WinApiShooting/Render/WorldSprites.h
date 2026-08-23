#pragma once
#include "Sprite.h"
#include "SpriteSheet.h"
#include <string>

class WorldSprites
{
public:
    bool load(const std::wstring& spaceRageRoot);

    Sprite background;
    Sprite promo;
    Sprite playerBlue[5]{};
    Sprite playerRed[5]{};
    Sprite playerShadow[5]{};
    Sprite enemy1[3][5]{};
    Sprite enemy2[3][5]{};
    Sprite enemy1Shadow[5]{};
    Sprite enemy2Shadow[5]{};
    SpriteSheet mineSeeker;
    SpriteSheet mineSentry;
    SpriteSheet mineBurst;
    SpriteSheet sawPatrol;
    SpriteSheet sawChase;
    SpriteSheet mineOrbit;
    SpriteSheet mine1Shadow;
    SpriteSheet mine2Shadow;
    SpriteSheet exhaust;
    SpriteSheet explosion1;
    SpriteSheet explosion2;
    SpriteSheet explosion3;
    Sprite vulcan[3]{};
    Sprite plasma[2]{};
    Sprite proton[3]{};
};
