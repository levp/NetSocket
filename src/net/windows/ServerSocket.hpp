#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include "../../FAIL.hpp"
#include "ClientSocket.hpp"

class ServerSocket final {
private:
	SOCKET serverSocket;
	addrinfo* addressInfo;

public:
	ServerSocket()
			: addressInfo{nullptr},
			  serverSocket{INVALID_SOCKET} {
	}

	~ServerSocket() {
		if (addressInfo != nullptr) {
			freeaddrinfo(addressInfo);
		}
		if (serverSocket != INVALID_SOCKET) {
			closesocket(serverSocket);
		}
	}

public:
	void bind(int port) {
		addressInfo = allocateAddress(port);
		serverSocket = allocateSocket(addressInfo);
		bindSocket(serverSocket, addressInfo);
		freeaddrinfo(addressInfo);
		addressInfo = nullptr;
		listenSocket(serverSocket);
	}

	ClientSocket acceptClient() {
		SOCKET clientSocket{accept(serverSocket, nullptr, nullptr)};
		if (clientSocket == INVALID_SOCKET) {
			FAIL("accept failed with error: ", WSAGetLastError());
		}
		return ClientSocket{clientSocket};
	}

private:
	static void listenSocket(SOCKET socket) {
		if (::listen(socket, SOMAXCONN) == SOCKET_ERROR) {
			FAIL("listen failed with error: ", WSAGetLastError());
		}
	}

	static void bindSocket(SOCKET socket, addrinfo* addressInfo) {
		int result{::bind(socket, addressInfo->ai_addr, (int) addressInfo->ai_addrlen)};
		if (result == SOCKET_ERROR) {
			FAIL("bind failed with error: ", WSAGetLastError());
		}
	}

	static SOCKET allocateSocket(addrinfo* addressInfo) {
		SOCKET serverSocket{::socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol)};
		if (serverSocket == INVALID_SOCKET) {
			FAIL("socket failed with error: ", WSAGetLastError());
		}
		return serverSocket;
	}

	static addrinfo* allocateAddress(int port) {
		addrinfo* addressInfo;

		addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		if (port < 0 || port > 65536) {
			FAIL("Invalid port, must be a value between 0 and 65536");
		}

		char strPort[6];
		std::snprintf(strPort, sizeof(strPort), "%d", port);
		int result{::getaddrinfo(nullptr, strPort, &hints, &addressInfo)};
		if (result != 0) {
			FAIL("getaddrinfo failed with error: ", result);
		}

		return addressInfo;
	}
};
