#include <iostream>

#include "src/Window.h"

void openConsole()
{
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    try
    {
        Window wnd(800, 300, L"Window View");
        MSG msg;
        BOOL gResult;

        openConsole();

        while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            throw CORE_EXCEPTION();
        }

        if (gResult == -1)
        {
            return gResult;
        }

        return msg.wParam;
    }
    catch (const CoreException& e)
    {
        MessageBox(nullptr, reinterpret_cast<LPCWSTR>(e.what()), reinterpret_cast<LPCWSTR>(e.GetType()), MB_OK | MB_ICONEXCLAMATION);
    }
    catch (const std::exception& e)
    {
        MessageBox(nullptr, reinterpret_cast<LPCWSTR>(e.what()), L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, L"No details available", L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
}
