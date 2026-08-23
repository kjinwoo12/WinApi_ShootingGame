#pragma once
#include "Common.h"
#include <random>

class RandomSource
{
public:
    float nextFloat(float lo, float hi)
    {
        std::uniform_real_distribution<float> dist(lo, hi);
        return dist(rng);
    }

    int nextInt(int lo, int hi)
    {
        std::uniform_int_distribution<int> dist(lo, hi);
        return dist(rng);
    }

private:
    std::mt19937 rng{std::random_device{}()};
};
