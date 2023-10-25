#pragma once

#define WIN_EXCEPTION(hr) Window::Exception(__LINE__, __FILE__, hr)
#define WIN_EXCEPTION_LAST() Window::Exception(__LINE__, __FILE__, GetLastError())