#pragma once
#include "Common.h"

// GDI+ 수명 + timer resolution. App/Game(Sprite)보다 바깥에서 살아 있어야 함.
class GdiplusRuntime
{
public:
    GdiplusRuntime();
    ~GdiplusRuntime();

    GdiplusRuntime(const GdiplusRuntime&) = delete;
    GdiplusRuntime& operator=(const GdiplusRuntime&) = delete;

    bool ok() const
    {
        return started;
    }

private:
    ULONG_PTR token = 0;
    bool started = false;
    bool timerPeriod = false;
};
