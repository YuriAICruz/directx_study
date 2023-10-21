#pragma once
#include <string>

#include "ModExports.h"
#include "ModWindows.h"

static class CORE_API WstrExtensions
{
public:
    static std::wstring LparamToWstr(LPARAM lparam) noexcept
    {
        std::wstring result = std::wstring((LPCTSTR)lparam);
        return result;
    }
    
    static LPARAM WstrToLparam(const wchar_t* string) noexcept
    {
        return LPARAM((LPCTSTR)string);
    }
    
    static std::wstring StrToWstr(char* str) noexcept
    {
        std::string s = str;
        return StrToWstr(s);
    }

    static std::wstring StrToWstr(std::string str) noexcept
    {
        std::wstring result = std::wstring(str.begin(), str.end());

        return result;
    }
};
