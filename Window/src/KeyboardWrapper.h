#pragma once
#include <bitset>
#include <optional>
#include <queue>

class KeyboardWrapper
{
    friend class Window;

public:
    class Event
    {
    public:
        enum class Type
        {
            Press,
            Release,
            Invalid
        };

    private:
        Type type;
        unsigned char code;
    public:
        Event() noexcept
            : type(Type::Invalid), code(0u)
        {
        }
        Event(Type type, unsigned char code) noexcept
            : type(type), code(code)
        {
        }

        bool IsPress() const noexcept
        {
            return type == Type::Press;
        }

        bool IsRelease() const noexcept
        {
            return type == Type::Release;
        }

        bool IsValid() const noexcept
        {
            return type != Type::Invalid;
        }

        unsigned char GetCode() const noexcept
        {
            return code;
        }
    };

public:
    KeyboardWrapper() = default;
    KeyboardWrapper(const KeyboardWrapper&) = delete;
    KeyboardWrapper& operator=(const KeyboardWrapper&) = delete;
    // key event stuff
    bool KeyIsPressed(unsigned char keycode) const noexcept;
    std::optional<Event> ReadKey() noexcept;
    bool KeyIsEmpty() const noexcept;
    void FlushKey() noexcept;
    // char event stuff
    std::optional<char> ReadChar() noexcept;
    bool CharIsEmpty() const noexcept;
    void FlushChar() noexcept;
    void Flush() noexcept;
    // autorepeat control
    void EnableAutorepeat() noexcept;
    void DisableAutorepeat() noexcept;
    bool AutorepeatIsEnabled() const noexcept;
private:
    void OnKeyPressed(unsigned char keycode) noexcept;
    void OnKeyReleased(unsigned char keycode) noexcept;
    void OnChar(char character) noexcept;
    void ClearState() noexcept;
    template <typename T>
    static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
    static constexpr unsigned int nKeys = 256u;
    static constexpr unsigned int bufferSize = 16u;
    bool autorepeatEnabled = false;
    std::bitset<nKeys> keystates;
    std::queue<Event> keyBuffer;
    std::queue<char> charBuffer;
};

template <typename T>
void KeyboardWrapper::TrimBuffer(std::queue<T>& buffer) noexcept
{
    while (buffer.size() > bufferSize)
    {
        buffer.pop();
    }
}
