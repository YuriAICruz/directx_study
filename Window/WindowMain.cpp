#include <iostream>
#include "WstrExtensions.h"
#include "src/App.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    try
    {
        return App{}.Go();
    }
    catch (const CoreException& e)
    {
        MessageBox(nullptr, WstrExtensions::StrToWstr(e.what()).c_str(), WstrExtensions::StrToWstr(e.GetType()).c_str(), MB_OK | MB_ICONEXCLAMATION);
    }
    catch (const std::exception& e)
    {
        MessageBox(nullptr, WstrExtensions::StrToWstr(e.what()).c_str(), L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, L"No details available", L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
}
