#pragma once
#include "Timer.h"
#include "Window.h"

class App
{
public:
    App();
    int Go();
private:
    void DoFrame();
private:
	Timer timer;
    Window wnd;
};
