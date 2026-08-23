#include "GdiplusRuntime.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
                      _In_ LPWSTR, _In_ int nCmdShow)
{
    GdiplusRuntime gdiplus;
    if (!gdiplus.ok())
        return 1;
    WinApp app;
    return app.run(hInstance, nCmdShow);
}
