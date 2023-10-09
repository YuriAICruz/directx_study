#include <iostream>

#include "src/Window.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    Window wnd(800,300, L"Window View");
    MSG msg;
    BOOL gResult;

    while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if(gResult == -1)
    {
        return gResult;
    }
    
    return msg.wParam;
}
