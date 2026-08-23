#pragma once
#include "AppContext.h"

class WinApp
{
public:
    int run(HINSTANCE instance, int nCmdShow);

private:
    static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static AppContext* contextFrom(HWND hwnd);

    bool registerClass(HINSTANCE instance);
    bool createWindow(HINSTANCE instance);
    int messageLoop();
    void destroyWindow();

    AppContext app;
    HWND hwnd = nullptr;
};
