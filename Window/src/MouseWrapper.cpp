#include "MouseWrapper.h"

#include <sstream>

#include "ModWindows.h"
#include "WstrExtensions.h"


std::pair<int, int> MouseWrapper::GetPos() const noexcept
{
    return {x, y};
}

int MouseWrapper::GetPosX() const noexcept
{
    return x;
}

int MouseWrapper::GetPosY() const noexcept
{
    return y;
}

bool MouseWrapper::IsInWindow() const noexcept
{
    return isInWindow;
}

bool MouseWrapper::LeftIsPressed() const noexcept
{
    return leftIsPressed;
}

bool MouseWrapper::RightIsPressed() const noexcept
{
    return rightIsPressed;
}

std::optional<MouseWrapper::Event> MouseWrapper::Read() noexcept
{
    if (buffer.size() > 0u)
    {
        MouseWrapper::Event e = buffer.front();
        buffer.pop();
        return e;
    }
    return {};
}

void MouseWrapper::Flush() noexcept
{
    buffer = std::queue<Event>();
}

void MouseWrapper::OnMousMove(int X, int Y) noexcept
{
    x = X;
    y = Y;

    std::ostringstream os;
    os << "(" << x << "," << y << ")\n";
    //OutputDebugStringW(WstrExtensions::StrToWstr(os.str()).c_str());

    buffer.push(MouseWrapper::Event(Event::Type::Move, *this));
}

void MouseWrapper::OnMouseLeave() noexcept
{
    isInWindow = false;

    OutputDebugStringW(L"OnMouseLeave\n");
    
    buffer.push(MouseWrapper::Event(Event::Type::Leave, *this));
    TrimBuffer();
}

void MouseWrapper::OnMouseEnter() noexcept
{
    isInWindow = true;
    
    OutputDebugStringW(L"OnMouseEnter\n");
    
    buffer.push(MouseWrapper::Event(Event::Type::Enter, *this));
    TrimBuffer();
}

void MouseWrapper::OnLeftPressed(int x, int y) noexcept
{
    OutputDebugStringW(L"OnLeftPressed\n");
    buffer.push(MouseWrapper::Event(Event::Type::LPress, *this));
}

void MouseWrapper::OnLeftReleased(int x, int y) noexcept
{
    OutputDebugStringW(L"OnLeftReleased\n");
    buffer.push(MouseWrapper::Event(Event::Type::LRelease, *this));
}

void MouseWrapper::OnRightPressed(int x, int y) noexcept
{
    OutputDebugStringW(L"OnRightPressed\n");
    buffer.push(MouseWrapper::Event(Event::Type::RPress, *this));
}

void MouseWrapper::OnRightReleased(int x, int y) noexcept
{
    OutputDebugStringW(L"OnRightReleased\n");
    buffer.push(MouseWrapper::Event(Event::Type::RRelease, *this));
}

void MouseWrapper::OnWheelUp(int x, int y) noexcept
{
    OutputDebugStringW(L"OnWheelUp\n");
    buffer.push(MouseWrapper::Event(Event::Type::WheelUp, *this));
}

void MouseWrapper::OnWheelDown(int x, int y) noexcept
{
    OutputDebugStringW(L"OnWheelDown\n");
    buffer.push(MouseWrapper::Event(Event::Type::WheelDown, *this));
}

void MouseWrapper::TrimBuffer() noexcept
{
    while (buffer.size() > bufferSize)
    {
        buffer.pop();
    }
}

void MouseWrapper::OneWheelDelta(int x, int y, int delta) noexcept
{
    wheelDeltaCarry += delta;
    // generate events for every 120 
    while (wheelDeltaCarry >= WHEEL_DELTA)
    {
        wheelDeltaCarry -= WHEEL_DELTA;
        OnWheelUp(x, y);
    }
    while (wheelDeltaCarry <= -WHEEL_DELTA)
    {
        wheelDeltaCarry += WHEEL_DELTA;
        OnWheelDown(x, y);
    }
    
    std::ostringstream os;
    os << "wheelDeltaCarry " << wheelDeltaCarry << "\n";
    OutputDebugStringW(WstrExtensions::StrToWstr(os.str().c_str()).c_str());
}
