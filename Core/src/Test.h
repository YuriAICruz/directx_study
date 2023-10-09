#pragma once
#include "ModWindows.h"

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

namespace Test
{
    class CORE_API Test
    {
    public:
        static const WCHAR* Tester();
    };
}
