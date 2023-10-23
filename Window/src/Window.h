#pragma once
#include "CoreException.h"
#include "KeyboardWrapper.h"
#include "ModWindows.h"

class Window
{
public:
    class Exception : public CoreException
    {
    public:
        Exception(int line, const char* file, HRESULT hr) noexcept;
        const char* what() const noexcept override;
        const char* GetType() const noexcept override;
        static std::string TranslateErrorCode(HRESULT hr) noexcept;
        HRESULT GetErrorCode() const noexcept;
        std::string GetErrorString() const noexcept;
    private:
        HRESULT hr;
    };

private:
    class WindowClass
    {
    public:
        static LPCWSTR GetName() noexcept;
        static HINSTANCE GetInstance() noexcept;
    private:
        WindowClass() noexcept;
        ~WindowClass();
        WindowClass(const WindowClass&) = delete;
        WindowClass& operator=(const WindowClass&) = delete;
        static constexpr LPCWSTR wndClassName = L"Direct3D Engine Window";
        static WindowClass wndClass;
        HINSTANCE hInst;
    };

public:
    Window(int width, int height, LPCWSTR name);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
private:
    static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    static LRESULT WINAPI HandleMsgTrunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

    KeyboardWrapper kbd;
    int width;
    int height;
    HWND hWnd;
};

#define WIN_EXCEPTION(hr) Window::Exception(__LINE__, __FILE__, hr)
#define WIN_EXCEPTION_LAST() Window::Exception(__LINE__, __FILE__, GetLastError())
