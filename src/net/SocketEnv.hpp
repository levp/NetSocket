#pragma once

#if WIN32
#include "platform/windows/WinSocketEnv.hpp"
#endif

class SocketEnv final {
#if WIN32
private:
	WinSocketEnv env;
#endif
};
