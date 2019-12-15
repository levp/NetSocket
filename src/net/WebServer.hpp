#pragma once

#include <atomic>
#include <functional>

#if WIN32
#include "platform/windows/ServerSocket.hpp"
#else
#include "platform/linux/ServerSocket.hpp"
#endif

class WebServer final {
private:
	std::atomic_bool running;
	ServerSocket serverSocket;

public:
	WebServer();

public:
	using SendResponse = std::function<void(std::string_view response)>;
	using OnRequest = std::function<void(std::string_view request, SendResponse& sendResponse)>;

	void bind(int port);
	void listen(OnRequest onRequest);
	void stop();
};
