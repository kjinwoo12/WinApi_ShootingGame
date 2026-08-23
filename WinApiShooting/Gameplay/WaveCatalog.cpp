#include "WaveCatalog.h"

bool WaveCatalog::isMidBossWave(int wave, int sector)
{
    return sector >= 5 && sector % 5 == 0 && (wave - 1) % 3 == 0;
}

WavePlan WaveCatalog::planForWave(int wave)
{
    // wave 1..12 고정 스케줄. 이후 = late 테이블 순환.
    static constexpr FormationId kLate[] = {
        FormationId::F11MixedWall,
        FormationId::F12ChaseSaws,
        FormationId::F09RedRush,
        FormationId::F08SawGate,
        FormationId::F06MineField,
        FormationId::F10BurstTrap,
    };

    struct Entry
    {
        int count;
        FormationId a;
        FormationId b;
        bool bonusFighter;
    };

    static constexpr Entry kFixed[] = {
        {1, FormationId::F01Column, FormationId::F01Column, false},
        {1, FormationId::F02Line, FormationId::F01Column, false},
        {1, FormationId::F03Vee, FormationId::F01Column, true},
        {2, FormationId::F04Diagonal, FormationId::F05HunterPair, false},
        {2, FormationId::F03Vee, FormationId::F06MineField, false},
        {2, FormationId::F05HunterPair, FormationId::F06MineField, false},
        {2, FormationId::F07SentryLine, FormationId::F02Line, false},
        {2, FormationId::F08SawGate, FormationId::F05HunterPair, false},
        {2, FormationId::F06MineField, FormationId::F08SawGate, false},
        {1, FormationId::F09RedRush, FormationId::F01Column, false},
        {2, FormationId::F10BurstTrap, FormationId::F04Diagonal, false},
        {2, FormationId::F09RedRush, FormationId::F10BurstTrap, false},
    };

    WavePlan plan{};
    if (wave >= 1 && wave <= 12)
    {
        const Entry& e = kFixed[wave - 1];
        plan.count = e.count;
        plan.forms[0] = e.a;
        if (e.count > 1)
            plan.forms[1] = e.b;
        plan.bonusFighter = e.bonusFighter;
        return plan;
    }

    plan.count = 2;
    plan.forms[0] = kLate[(wave + 0) % 6];
    plan.forms[1] = kLate[(wave + 3) % 6];
    return plan;
}
