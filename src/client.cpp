#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <string>
#include <chrono>

typedef websocketpp::client<websocketpp::config::asio_client> websocket_client;

int main(int argc, char* argv[]) {
	std::string uri = "ws://127.0.0.1:9002";
	std::string message = "Hello from C++ client";
	if (argc >= 2) {
		uri = argv[1];
	}
	if (argc >= 3) {
		message = argv[2];
	}

	websocket_client client;
	websocketpp::lib::error_code ec;

	client.clear_access_channels(websocketpp::log::alevel::all);
	client.set_access_channels(websocketpp::log::alevel::connect | websocketpp::log::alevel::disconnect | websocketpp::log::alevel::app);

	client.init_asio();

	client.set_open_handler([&client, &message](websocketpp::connection_hdl hdl) {
		client.get_alog().write(websocketpp::log::alevel::app, "Connected, sending message");
		websocketpp::lib::error_code send_ec;
		client.send(hdl, message, websocketpp::frame::opcode::text, send_ec);
		if (send_ec) {
			std::cerr << "Send failed: " << send_ec.message() << std::endl;
		}
	});

	client.set_message_handler([&client](websocketpp::connection_hdl hdl, websocket_client::message_ptr msg) {
		std::cout << "Received: " << msg->get_payload() << std::endl;
		websocketpp::lib::error_code close_ec;
		client.close(hdl, websocketpp::close::status::normal, "done", close_ec);
	});

	client.set_fail_handler([&client](websocketpp::connection_hdl) {
		client.get_alog().write(websocketpp::log::alevel::app, "Connection failed");
	});

	auto con = client.get_connection(uri, ec);
	if (ec) {
		std::cerr << "Get connection error: " << ec.message() << std::endl;
		return 1;
	}

	client.connect(con);

	try {
		client.run();
	} catch (const std::exception& ex) {
		std::cerr << "Client exception: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}