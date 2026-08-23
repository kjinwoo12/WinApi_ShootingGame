#include "EnemyBehaviors.h"
#include "FighterBehavior.h"
#include "MidBossBehavior.h"
#include "MineBurstBehavior.h"
#include "MineSeekerBehavior.h"
#include "MineSentryBehavior.h"
#include "OrbitMineBehavior.h"
#include "SawChaseBehavior.h"
#include "SawPatrolBehavior.h"
#include "ScoutBehavior.h"
#include <array>
#include <cassert>

static constexpr int kKindCount = static_cast<int>(EnemyKind::OrbitMine) + 1;

static const ScoutBehavior kScout{};
static const FighterBehavior kFighter{};
static const MineSeekerBehavior kMineSeeker{};
static const MineSentryBehavior kMineSentry{};
static const MineBurstBehavior kMineBurst{};
static const SawPatrolBehavior kSawPatrol{};
static const SawChaseBehavior kSawChase{};
static const MidBossBehavior kMidBoss{};
static const OrbitMineBehavior kOrbitMine{};

static const std::array<const IEnemyBehavior*, kKindCount> kTable = {
    &kScout,
    &kFighter,
    &kMineSeeker,
    &kMineSentry,
    &kMineBurst,
    &kSawPatrol,
    &kSawChase,
    &kMidBoss,
    &kOrbitMine,
};

const IEnemyBehavior& EnemyBehaviors::at(EnemyKind kind)
{
    const int i = static_cast<int>(kind);
    assert(i >= 0 && i < kKindCount);
    return *kTable[static_cast<size_t>(i)];
}
