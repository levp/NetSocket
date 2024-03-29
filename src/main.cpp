#include <string>
#include "net/SocketEnv.hpp"
#include "net/WebServer.hpp"

int main() {
	SocketEnv env;

	WebServer server;
	server.bind(8080);
	server.listen([](std::string_view request, WebServer::SendResponse& sendResponse) {
			sendResponse("HTTP/1.1 200\r\nContent-Type: text/html\r\n\r\n<h1>Hi!</h1>\r\n");
	});

	return EXIT_SUCCESS;
}
