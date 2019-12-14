#include "WinSocketEnv.hpp"

#include <winsock2.h>
#include "../../FAIL.hpp"

WinSocketEnv::WinSocketEnv() {
	WSADATA wsaData;
	int result{WSAStartup(MAKEWORD(2, 2), &wsaData)};
	if (result != 0) {
		FAIL("WSAStartup failed with error: ", result);
	}
}

WinSocketEnv::~WinSocketEnv() {
	WSACleanup();
}
