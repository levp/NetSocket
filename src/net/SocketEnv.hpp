#pragma once

#if WIN32
#include "windows/WinSocketEnv.hpp"
#endif

class SocketEnv final {
#if WIN32
private:
	WinSocketEnv env;
#endif
};
