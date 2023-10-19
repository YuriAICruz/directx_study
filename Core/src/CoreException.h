#pragma once
#include "ModExports.h"
#include <exception>
#include <string>

class CORE_API CoreException : public std::exception
{
public:
    CoreException(int line, const char* file) noexcept;
    const char* what() const noexcept override;
    virtual const char* GetType() const noexcept;
    int GetLine() const noexcept;
    const std::string& GetFile() const noexcept;
    const std::string GetOriginString() const noexcept;
private:
    int line;
    std::string file;
protected:
    mutable std::string whatBuffer;
};

#define CORE_EXCEPTION() CoreException(__LINE__, __FILE__)