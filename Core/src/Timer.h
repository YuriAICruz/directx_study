#pragma once
#include "ModExports.h"
#include <chrono>

class CORE_API Timer
{
public:
    Timer() noexcept;
    float Mark() noexcept;
    float Peek() const noexcept;
    float FromStart() const noexcept;
private:
    std::chrono::steady_clock::time_point last;
    std::chrono::steady_clock::time_point start;
};