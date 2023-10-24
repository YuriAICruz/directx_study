#pragma once
#include <string>

#include "ModExports.h"
#include "ModWindows.h"

static class CORE_API WstrExtensions
{
public:
    static std::wstring LparamToWstr(LPARAM lparam) noexcept
    {
        return std::wstring((LPCTSTR)lparam);
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

    static std::wstring LPWSTRToWstr(LPWSTR lpwstr)
    {
        return std::wstring(lpwstr);
    }

    static std::string LPWSTRToStr(LPWSTR lpwstr)
    {
        std::wstring ws(LPWSTRToWstr(lpwstr));
        std::string result;
        for (char x : ws)
            result += x;
        return result;
    }
};
