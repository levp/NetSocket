#pragma once

#include <string_view>
#include <winsock2.h>
#include "../../FAIL.hpp"

class ClientSocket final {
private:
	SOCKET clientSocket;

public:
	explicit ClientSocket(SOCKET clientSocket)
			: clientSocket{clientSocket} {
	}

public:
	std::string receiveRequest() {
		constexpr size_t bufferSize{4096};
		char buffer[bufferSize];
		int bytesReceived{recv(clientSocket, buffer, bufferSize, 0)};
		if (bytesReceived <= 0) {
			FAIL("recv failed with error: ", WSAGetLastError());
		}
		return std::string{buffer, static_cast<size_t>(bytesReceived)};
	}

	void write(std::string_view responseMessage) {
		int sendResult{send(clientSocket, responseMessage.data(), responseMessage.size(), 0)};
		if (sendResult == SOCKET_ERROR) {
			FAIL("send failed with error: ", WSAGetLastError());
		}
	}

	void end() {
		if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR) {
			FAIL("shutdown failed with error: ", WSAGetLastError());
		}
	}
};
