#include "WinApp.h"
#include "DeltaTime.h"

AppContext* WinApp::contextFrom(HWND hwnd)
{
    return reinterpret_cast<AppContext*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
}

LRESULT CALLBACK WinApp::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCTW* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA,
                          reinterpret_cast<LONG_PTR>(create->lpCreateParams));
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    AppContext* ctx = contextFrom(hwnd);

    switch (msg)
    {
    case WM_DESTROY:
        if (ctx)
            ctx->running = false;
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        if (ctx && (lParam & (1 << 30)) == 0)
            ctx->game.onKeyDown(wParam);
        return 0;
    case WM_KEYUP:
        if (ctx)
            ctx->game.onKeyUp(wParam);
        return 0;
    case WM_SYSKEYDOWN:
        if (wParam == VK_F4)
            break;
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT:
    {
        PAINTSTRUCT ps{};
        HDC hdc = BeginPaint(hwnd, &ps);
        if (ctx)
            ctx->game.render(hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

bool WinApp::registerClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = wndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wc.lpszClassName = L"SpaceRageWnd";
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    return RegisterClassExW(&wc) != 0;
}

bool WinApp::createWindow(HINSTANCE hInstance)
{
    RECT rc{0, 0, ScreenWidth, ScreenHeight};
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

    hwnd = CreateWindowExW(
        0, L"SpaceRageWnd", L"Space Rage — WinAPI Shooting",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        nullptr, nullptr, hInstance, &app);

    return hwnd != nullptr;
}

void WinApp::destroyWindow()
{
    if (!hwnd || !IsWindow(hwnd))
        return;
    SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
    DestroyWindow(hwnd);
    hwnd = nullptr;
}

int WinApp::messageLoop()
{
    DeltaTime clock;
    MSG msg{};

    while (app.running)
    {
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                app.running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        if (!app.running)
            break;

        app.game.update(clock.tick());

        HDC hdc = GetDC(hwnd);
        if (!hdc)
            continue;
        app.game.render(hdc);
        ReleaseDC(hwnd, hdc);
    }

    return static_cast<int>(msg.wParam);
}

int WinApp::run(HINSTANCE hInstance, int nCmdShow)
{
    if (!registerClass(hInstance))
    {
        MessageBoxW(nullptr, L"윈도우 클래스 등록에 실패했습니다.", L"Space Rage", MB_ICONERROR);
        return 1;
    }

    if (!createWindow(hInstance))
    {
        MessageBoxW(nullptr, L"윈도우 생성에 실패했습니다.", L"Space Rage", MB_ICONERROR);
        return 1;
    }

    if (!app.game.init(hwnd))
    {
        destroyWindow();
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    const int exitCode = messageLoop();
    destroyWindow();
    app.game.shutdown();
    return exitCode;
}
