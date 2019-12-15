#pragma once

#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include "../../FAIL.hpp"
#include "ClientSocket.hpp"

class ServerSocket final {
private:
	int serverSocket;
	sockaddr_in address;

public:
	ServerSocket()
			: serverSocket{-1} {
	}

	~ServerSocket() {
		if (serverSocket > 0) {
			close(serverSocket);
			serverSocket = -1;
		}
	}

public:
	void bind(int port) {
		allocateAddress(port, &address);
		serverSocket = allocateSocket();
		bindSocket(serverSocket, &address);
		listenSocket(serverSocket);
	}

	ClientSocket acceptClient() {
		int clientSocket{accept(serverSocket, nullptr, nullptr)};
		if (clientSocket < 0) {
			FAIL("Accept socket failed with error.");
		}
		return ClientSocket{clientSocket};
	}

private:
	static int allocateSocket() {
		return socket(
				/* ipv4 */ AF_INET,
				/* tcp  */ SOCK_STREAM,
				/* ip   */  0
		);
	}

	static void listenSocket(int socket) {
		if (::listen(socket, SOMAXCONN) < 0) {
			FAIL("Listen failed with error.");
		}
	}

	static void bindSocket(int socket, sockaddr_in* address) {
		if (::bind(socket, reinterpret_cast<sockaddr*>(address), sizeof(*address)) < 0) {
			FAIL("Failed to set bind socket.");
		}
	}

	static void allocateAddress(int port, sockaddr_in* address) {
		address->sin_family = AF_INET;
		address->sin_addr.s_addr = INADDR_ANY;
		address->sin_port = htons(port);
	}
};
