#pragma once
#include "FormationId.h"

struct WavePlan
{
    FormationId forms[4]{};
    int count = 0;
    bool bonusFighter = false;
};
