#include "DeltaTime.h"
#include "Common.h"

DeltaTime::DeltaTime()
{
    LARGE_INTEGER freq{};
    QueryPerformanceFrequency(&freq);
    frequency = freq.QuadPart;
    reset();
}

void DeltaTime::reset()
{
    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    lastCounter = now.QuadPart;
}

float DeltaTime::tick(float maxSeconds)
{
    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    const float dt = static_cast<float>(now.QuadPart - lastCounter) /
                     static_cast<float>(frequency);
    lastCounter = now.QuadPart;
    return clampFloat(dt, 0.f, maxSeconds);
}
