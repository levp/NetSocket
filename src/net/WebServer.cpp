#include "WebServer.hpp"

WebServer::WebServer()
		: running{false} {
}

void WebServer::bind(int port) {
	serverSocket.bind(8080);
}

void WebServer::listen(WebServer::OnRequest onRequest) {

	running = true;
	while (running) {
		ClientSocket client{serverSocket.acceptClient()};
		std::string request{client.receiveRequest()};

		SendResponse sendResponse{[&client](std::string_view response) {
				client.write(response);
				client.end();
		}};

		onRequest(request, sendResponse);
	}
}

void WebServer::stop() {
	running = false;
}
