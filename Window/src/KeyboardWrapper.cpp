#include "KeyboardWrapper.h"

#include <sstream>
#include <string>
#include "WstrExtensions.h"

bool KeyboardWrapper::KeyIsPressed(unsigned char keycode) const noexcept
{
    return keystates[keycode];
}

std::optional<KeyboardWrapper::Event> KeyboardWrapper::ReadKey() noexcept
{
    if (keyBuffer.size() > 0u)
    {
        KeyboardWrapper::Event e = keyBuffer.front();
        keyBuffer.pop();
        return e;
    }

    return KeyboardWrapper::Event();
}

bool KeyboardWrapper::KeyIsEmpty() const noexcept
{
    return keyBuffer.empty();
}

void KeyboardWrapper::FlushKey() noexcept
{
    keyBuffer = std::queue<Event>();
}

std::optional<char> KeyboardWrapper::ReadChar() noexcept
{
    if (charBuffer.size() > 0u)
    {
        unsigned char charcode = charBuffer.front();
        charBuffer.pop();
        return charcode;
    }

    return 0;
}

bool KeyboardWrapper::CharIsEmpty() const noexcept
{
    return charBuffer.empty();
}

void KeyboardWrapper::FlushChar() noexcept
{
    charBuffer = std::queue<char>();
}

void KeyboardWrapper::Flush() noexcept
{
    FlushKey();
    FlushChar();
}

void KeyboardWrapper::EnableAutorepeat() noexcept
{
    autorepeatEnabled = true;
}

void KeyboardWrapper::DisableAutorepeat() noexcept
{
    autorepeatEnabled = false;
}

bool KeyboardWrapper::AutorepeatIsEnabled() const noexcept
{
    return autorepeatEnabled;
}

void KeyboardWrapper::OnKeyPressed(unsigned char keycode) noexcept
{
    std::ostringstream os;
    os << "Key Pressed " << keycode << "\n";
    OutputDebugString(WstrExtensions::StrToWstr(os.str().c_str()).c_str());
    
    keystates[keycode] = true;
    keyBuffer.push(KeyboardWrapper::Event(KeyboardWrapper::Event::Type::Press, keycode));
    TrimBuffer(keyBuffer);
}

void KeyboardWrapper::OnKeyReleased(unsigned char keycode) noexcept
{
    std::ostringstream os;
    os << "Key Released " << keycode << "\n";
    OutputDebugStringW(WstrExtensions::StrToWstr(os.str().c_str()).c_str());
    
    keystates[keycode] = false;
    keyBuffer.push(KeyboardWrapper::Event(KeyboardWrapper::Event::Type::Release, keycode));
    TrimBuffer(keyBuffer);
}

void KeyboardWrapper::OnChar(char character) noexcept
{
    std::ostringstream os;
    os << "Char received " << character << "\n";
    OutputDebugStringW(WstrExtensions::StrToWstr(os.str().c_str()).c_str());

    charBuffer.push(character);
    TrimBuffer(charBuffer);
}

void KeyboardWrapper::ClearState() noexcept
{
    keystates.reset();
}
