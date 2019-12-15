#pragma once

#include <string_view>
#include "../../FAIL.hpp"

class ClientSocket final {
private:
	int clientSocket;

public:
	explicit ClientSocket(int clientSocket)
			: clientSocket{clientSocket} {
	}

public:
	std::string receiveRequest() {
		constexpr size_t bufferSize{4096};
		char buffer[bufferSize];
		ssize_t bytesReceived{recv(clientSocket, buffer, bufferSize, 0)};
		if (bytesReceived < 0) {
			FAIL("Failed to read data from client socket.");
		}
		return std::string{buffer, static_cast<size_t>(bytesReceived)};
	}

	void write(std::string_view responseMessage) {
		ssize_t sendResult{send(clientSocket, responseMessage.data(), responseMessage.size(), 0)};
		if (sendResult < 0) {
			FAIL("Failed sending response to client socket.");
		}
	}

	void end() {
		if (shutdown(clientSocket, SHUT_RDWR) < 0) {
			FAIL("shutdown failed with error.");
		}
	}
};
