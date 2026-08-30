#include "GdiplusRuntime.h"
#include <gdiplus.h>
#include <mmsystem.h>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

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
