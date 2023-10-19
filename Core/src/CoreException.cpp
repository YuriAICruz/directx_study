#include "CoreException.h"
#include <sstream>

CoreException::CoreException(int line, const char* file) noexcept : line(line), file(file)
{
}

const char* CoreException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << std::endl
        << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* CoreException::GetType() const noexcept
{
    return "Core Exception";
}


int CoreException::GetLine() const noexcept
{
    return line;
}


const std::string& CoreException::GetFile() const noexcept
{
    return file;
}


const std::string CoreException::GetOriginString() const noexcept
{
    std::ostringstream oss;
    oss << "[line] " << line << std::endl
        << " [file] " << file;
    return oss.str();
}
