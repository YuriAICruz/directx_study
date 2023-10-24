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
    
    wnd.Gfx().EndFrame();
}
