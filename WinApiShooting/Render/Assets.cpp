#include "Assets.h"

namespace
{

std::wstring joinPath(const std::wstring& a, const std::wstring& b)
{
    if (a.empty())
        return b;
    if (a.back() == L'\\' || a.back() == L'/')
        return a + b;
    return a + L"\\" + b;
}

using SpritePick = const Sprite& (*)(const WorldSprites& w, const Enemy& e);

const Sprite& pickEnemy1(const WorldSprites& w, const Enemy& e)
{
    return w.enemy1[clampInt(e.color, 0, 2)][clampInt(e.bank, 0, 4)];
}

const Sprite& pickEnemy2(const WorldSprites& w, const Enemy& e)
{
    return w.enemy2[clampInt(e.color, 0, 2)][clampInt(e.bank, 0, 4)];
}

const Sprite& pickMineSeeker(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.mineSeeker.at(frame % w.mineSeeker.count());
}

const Sprite& pickMineSentry(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.mineSentry.at(frame % w.mineSentry.count());
}

const Sprite& pickMineBurst(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.mineBurst.at(frame % w.mineBurst.count());
}

const Sprite& pickSawPatrol(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.sawPatrol.at(frame % w.sawPatrol.count());
}

const Sprite& pickSawChase(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.sawChase.at(frame % w.sawChase.count());
}

const Sprite& pickMineOrbit(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.mineOrbit.at(frame % w.mineOrbit.count());
}

const Sprite& pickEnemy1Shadow(const WorldSprites& w, const Enemy& e)
{
    return w.enemy1Shadow[clampInt(e.bank, 0, 4)];
}

const Sprite& pickEnemy2Shadow(const WorldSprites& w, const Enemy& e)
{
    return w.enemy2Shadow[clampInt(e.bank, 0, 4)];
}

const Sprite& pickMine1Shadow(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.mine1Shadow.at(frame % w.mine1Shadow.count());
}

const Sprite& pickMine2Shadow(const WorldSprites& w, const Enemy& e)
{
    const int frame = static_cast<int>(e.anim);
    return w.mine2Shadow.at(frame % w.mine2Shadow.count());
}

constexpr int kKindCount = static_cast<int>(EnemyKind::OrbitMine) + 1;

static constexpr SpritePick kEnemySprite[kKindCount] = {
    pickEnemy1,
    pickEnemy2,
    pickMineSeeker,
    pickMineSentry,
    pickMineBurst,
    pickSawPatrol,
    pickSawChase,
    pickEnemy2,
    pickMineOrbit,
};

static constexpr SpritePick kEnemyShadow[kKindCount] = {
    pickEnemy1Shadow,
    pickEnemy2Shadow,
    pickMine1Shadow,
    pickMine1Shadow,
    pickMine1Shadow,
    pickMine2Shadow,
    pickMine2Shadow,
    pickEnemy2Shadow,
    pickMine2Shadow,
};

} // namespace

bool Assets::load(HWND ownerWindow)
{
    if (!resolveRoot(ownerWindow))
        return false;
    if (!world_.load(root))
    {
        MessageBoxW(ownerWindow,
                    L"이미지 에셋 로드에 실패했습니다.\n"
                    L"Assets\\SpaceRage 파일이 손상되었거나 이름이 맞는지 확인하세요.",
                    L"Space Rage", MB_ICONERROR);
        return false;
    }
    if (!ui_.load(root))
    {
        MessageBoxW(ownerWindow,
                    L"HUD 에셋 로드에 실패했습니다.\n"
                    L"Assets\\WenrexaUi 폴더와 PNG를 확인하세요.",
                    L"Space Rage", MB_ICONERROR);
        return false;
    }
    return true;
}

bool Assets::resolveRoot(HWND ownerWindow)
{
    wchar_t modulePath[MAX_PATH]{};
    GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
    std::wstring dir(modulePath);
    const size_t slash = dir.find_last_of(L"\\/");
    if (slash != std::wstring::npos)
        dir.resize(slash);

    const std::wstring candidates[] = {
        joinPath(dir, L"Assets\\SpaceRage"),
        joinPath(dir, L"..\\Assets\\SpaceRage"),
        joinPath(dir, L"..\\..\\Assets\\SpaceRage"),
        joinPath(dir, L"..\\..\\..\\Assets\\SpaceRage"),
        joinPath(dir, L"..\\..\\..\\WinApiShooting\\Assets\\SpaceRage"),
        joinPath(dir, L"..\\..\\WinApiShooting\\Assets\\SpaceRage"),
        L"Assets\\SpaceRage",
        L"..\\Assets\\SpaceRage",
        L"WinApiShooting\\Assets\\SpaceRage",
    };

    for (const std::wstring& candidate : candidates)
    {
        const std::wstring probe = joinPath(candidate, L"BG.png");
        const DWORD attr = GetFileAttributesW(probe.c_str());
        if (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY))
        {
            wchar_t full[MAX_PATH]{};
            if (GetFullPathNameW(candidate.c_str(), MAX_PATH, full, nullptr))
            {
                root = full;
            }
            else
            {
                root = candidate;
            }
            return true;
        }
    }

    MessageBoxW(ownerWindow,
                L"Assets\\SpaceRage 폴더를 찾을 수 없습니다.\n"
                L"실행 작업 디렉터리를 프로젝트 폴더로 설정했는지 확인하세요.",
                L"Space Rage", MB_ICONERROR);
    return false;
}

const Sprite& Assets::playerSprite(int bank, bool rage) const
{
    bank = clampInt(bank, 0, 4);
    return rage ? world_.playerRed[bank] : world_.playerBlue[bank];
}

const Sprite& Assets::playerShadowSprite(int bank) const
{
    return world_.playerShadow[clampInt(bank, 0, 4)];
}

const Sprite& Assets::enemySprite(const Enemy& enemy) const
{
    const int i = static_cast<int>(enemy.kind);
    if (i < 0 || i >= kKindCount)
        return pickEnemy1(world_, enemy);
    return kEnemySprite[i](world_, enemy);
}

const Sprite& Assets::enemyShadowSprite(const Enemy& enemy) const
{
    const int i = static_cast<int>(enemy.kind);
    if (i < 0 || i >= kKindCount)
        return pickEnemy1Shadow(world_, enemy);
    return kEnemyShadow[i](world_, enemy);
}

const Sprite& Assets::bulletSprite(const Bullet& bullet) const
{
    if (bullet.spriteIndex >= 0)
    {
        if (bullet.weapon == WeaponLevel::Proton && bullet.spriteIndex < 3)
            return world_.proton[bullet.spriteIndex];
        if (bullet.weapon == WeaponLevel::Plasma && bullet.spriteIndex < 2)
            return world_.plasma[bullet.spriteIndex];
        if (bullet.weapon == WeaponLevel::Vulcan && bullet.spriteIndex < 3)
            return world_.vulcan[bullet.spriteIndex];
    }

    const Sprite* byWeapon[] = {&world_.vulcan[1], &world_.plasma[0], &world_.proton[0]};
    const int w = static_cast<int>(bullet.weapon);
    if (w < 0 || w > 2)
        return world_.vulcan[0];
    return *byWeapon[w];
}

const Sprite& Assets::explosionSprite(int type, int frame) const
{
    if (type == 0)
        return world_.explosion1.at(frame);
    if (type == 1)
        return world_.explosion2.at(frame);
    return world_.explosion3.at(frame);
}

const Sprite& Assets::exhaustSprite(int frame) const
{
    return world_.exhaust.at(frame % world_.exhaust.count());
}

BulletDrawParams Assets::bulletDrawParams(const Bullet& bullet) const
{
    BulletDrawParams params;
    if (std::fabs(bullet.vel.x) > 1.f || std::fabs(bullet.vel.y) > 1.f)
        params.rotationDeg = std::atan2(bullet.vel.y, bullet.vel.x) * (180.f / Pi) + 90.f;
    if (bullet.weapon == WeaponLevel::Proton)
        params.scale = 1.6f;
    else if (bullet.weapon == WeaponLevel::Plasma)
        params.scale = 1.3f;
    else
        params.scale = 1.8f;
    return params;
}

const Sprite& Assets::powerUpFrame() const
{
    return ui_.hexFrame;
}

const Sprite& Assets::hudWeaponIcon(WeaponLevel weapon) const
{
    if (weapon == WeaponLevel::Plasma)
        return world_.plasma[0];
    if (weapon == WeaponLevel::Proton)
        return world_.proton[0];
    return world_.vulcan[1];
}

const Sprite& Assets::hudLifeShip() const
{
    return world_.playerBlue[2];
}

const Sprite& Assets::hudLifeSlot() const
{
    return ui_.lifeSlot;
}

const Sprite& Assets::hudBossTrack() const
{
    return ui_.sliderTrack;
}

const Sprite& Assets::hudPanel() const
{
    return ui_.mainHud;
}

const Sprite& Assets::hudSectorBanner() const
{
    return ui_.btnBanner;
}

const Sprite& Assets::titlePromo() const
{
    return world_.promo;
}

const Sprite& Assets::titleStrip() const
{
    return ui_.titleStrip;
}

const Sprite& Assets::titleStartButton() const
{
    return ui_.btnStart;
}

const Sprite& Assets::titleHighScoreStrip() const
{
    return ui_.hiStrip;
}

const Sprite& Assets::resultPanel() const
{
    return ui_.mainResult;
}

float Assets::backgroundHeight() const
{
    return static_cast<float>(world_.background.height());
}

int Assets::exhaustFrameCount() const
{
    return world_.exhaust.count();
}

const Sprite& Assets::backgroundSprite() const
{
    return world_.background;
}
