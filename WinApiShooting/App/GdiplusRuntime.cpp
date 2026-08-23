#include "GdiplusRuntime.h"
#include <mmsystem.h>

GdiplusRuntime::GdiplusRuntime()
{
    timeBeginPeriod(1);
    timerPeriod = true;

    Gdiplus::GdiplusStartupInput input;
    if (Gdiplus::GdiplusStartup(&token, &input, nullptr) != Gdiplus::Ok)
    {
        MessageBoxW(nullptr, L"GDI+ 초기화 실패", L"Space Rage", MB_ICONERROR);
        return;
    }
    started = true;
}

GdiplusRuntime::~GdiplusRuntime()
{
    if (started)
    {
        Gdiplus::GdiplusShutdown(token);
        token = 0;
        started = false;
    }
    if (timerPeriod)
    {
        timeEndPeriod(1);
        timerPeriod = false;
    }
}
