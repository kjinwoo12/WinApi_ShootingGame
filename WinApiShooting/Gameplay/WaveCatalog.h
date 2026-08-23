#pragma once
#include "WavePlan.h"

namespace WaveCatalog
{
bool isMidBossWave(int wave, int sector);
WavePlan planForWave(int wave);
} // namespace WaveCatalog
