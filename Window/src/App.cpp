#include "App.h"

#include "WstrExtensions.h"

App::App() : wnd(800, 600, L"Engine")
{
}

int App::Go()
{
    while (true)
    {
        if (const auto exitCode = Window::ProcessMessage())
        {
            return *exitCode;
        }
        DoFrame();
    }
}

void App::DoFrame()
{
    auto dt = timer.Mark();

    const float s = sin(timer.FromStart()) * 0.5f + 0.5f;
    const float c = cos(timer.FromStart()) * 0.5f + 0.5f;
    const float t = tan(timer.FromStart()) * 0.5f + 0.5f;
    wnd.Gfx().ClearBuffer(s, c, t);
    wnd.Gfx().EndFrame();
}
