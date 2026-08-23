#include "WorldSprites.h"

namespace
{

constexpr const wchar_t* ColorTags[] = {L"b", L"g", L"r"};
constexpr const wchar_t* BankTags[] = {L"l2", L"l1", L"m", L"r1", L"r2"};

std::wstring joinPath(const std::wstring& a, const std::wstring& b)
{
    if (a.empty())
        return b;
    if (a.back() == L'\\' || a.back() == L'/')
        return a + b;
    return a + L"\\" + b;
}

} // namespace

bool WorldSprites::load(const std::wstring& root)
{
    if (!background.load(joinPath(root, L"BG.png")))
        return false;
    promo.load(joinPath(root, L"PromoPic.png"));

    const std::wstring playerDir = joinPath(root, L"Player");
    const std::wstring shadowDir = joinPath(root, L"Shadows");
    const std::wstring enemyDir = joinPath(root, L"Enemies");
    const std::wstring fxDir = joinPath(root, L"FX");
    const std::wstring explDir = joinPath(root, L"Explosions");

    for (int i = 0; i < 5; ++i)
    {
        if (!playerBlue[i].load(joinPath(playerDir, std::wstring(L"player_b_") + BankTags[i] + L".png")))
            return false;
        if (!playerRed[i].load(joinPath(playerDir, std::wstring(L"player_r_") + BankTags[i] + L".png")))
            return false;
        if (!playerShadow[i].load(joinPath(shadowDir, std::wstring(L"player_shadow_") + BankTags[i] + L".png")))
            return false;
        if (!enemy1Shadow[i].load(joinPath(shadowDir, std::wstring(L"enemy_1_shadow_") + BankTags[i] + L".png")))
            return false;
        if (!enemy2Shadow[i].load(joinPath(shadowDir, std::wstring(L"enemy_2_shadow_") + BankTags[i] + L".png")))
            return false;
    }

    for (int c = 0; c < 3; ++c)
    {
        for (int b = 0; b < 5; ++b)
        {
            const std::wstring e1 = joinPath(enemyDir, std::wstring(L"enemy_1_") + ColorTags[c] + L"_" + BankTags[b] + L".png");
            const std::wstring e2 = joinPath(enemyDir, std::wstring(L"enemy_2_") + ColorTags[c] + L"_" + BankTags[b] + L".png");
            if (!enemy1[c][b].load(e1))
                return false;
            if (!enemy2[c][b].load(e2))
                return false;
        }
    }

    if (!mineSeeker.loadFolder(enemyDir, L"mine_1_", 1, 9))
        return false;
    if (!mineSentry.loadFolder(enemyDir, L"mine_11_", 1, 9))
        return false;
    if (!mineBurst.loadFolder(enemyDir, L"mine_12_", 1, 9))
        return false;
    if (!sawPatrol.loadFolder(enemyDir, L"mine_2_", 1, 4))
        return false;
    if (!sawChase.loadFolder(enemyDir, L"mine_21_", 1, 4))
        return false;
    if (!mineOrbit.loadFolder(enemyDir, L"mine_22_", 1, 4))
        return false;
    if (!mine1Shadow.loadFolder(shadowDir, L"mine_1_shadow_", 1, 8))
        return false;
    if (!mine2Shadow.loadFolder(shadowDir, L"mine_2_shadow_", 1, 4))
        return false;
    if (!exhaust.loadFolder(fxDir, L"exhaust_", 1, 5))
        return false;
    if (!explosion1.loadFolder(explDir, L"explosion_1_", 1, 11))
        return false;
    if (!explosion2.loadFolder(explDir, L"explosion_2_", 1, 9))
        return false;
    if (!explosion3.loadFolder(explDir, L"explosion_3_", 1, 9))
        return false;

    if (!vulcan[0].load(joinPath(fxDir, L"vulcan_1.png")))
        return false;
    if (!vulcan[1].load(joinPath(fxDir, L"vulcan_2.png")))
        return false;
    if (!vulcan[2].load(joinPath(fxDir, L"vulcan_3.png")))
        return false;
    if (!plasma[0].load(joinPath(fxDir, L"plasma_1.png")))
        return false;
    if (!plasma[1].load(joinPath(fxDir, L"plasma_2.png")))
        return false;
    if (!proton[0].load(joinPath(fxDir, L"proton_01.png")))
        return false;
    if (!proton[1].load(joinPath(fxDir, L"proton_02.png")))
        return false;
    if (!proton[2].load(joinPath(fxDir, L"proton_03.png")))
        return false;

    return true;
}
