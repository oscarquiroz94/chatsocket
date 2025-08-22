#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include <csignal>
#include <atomic>

using websocketpp::connection_hdl;

typedef websocketpp::server<websocketpp::config::asio> websocket_server;

static std::atomic<bool> g_should_stop{false};

void signal_handler(int) {
	g_should_stop.store(true);
}

int main(int argc, char* argv[]) {
	// Parse optional port argument
	uint16_t port = 9002;
	if (argc >= 2) {
		try {
			int p = std::stoi(argv[1]);
			if (p > 0 && p < 65536) {
				port = static_cast<uint16_t>(p);
			}
		} catch (...) {
			std::cerr << "Invalid port, using default 9002\n";
		}
	}

	std::signal(SIGINT, signal_handler);
	std::signal(SIGTERM, signal_handler);

	websocket_server server;

	try {
		server.clear_access_channels(websocketpp::log::alevel::all);
		server.set_access_channels(websocketpp::log::alevel::connect | websocketpp::log::alevel::disconnect | websocketpp::log::alevel::app);

		server.init_asio();

		server.set_open_handler([&server](connection_hdl hdl) {
			server.get_alog().write(websocketpp::log::alevel::app, "Client connected");
		});

		server.set_close_handler([&server](connection_hdl hdl) {
			server.get_alog().write(websocketpp::log::alevel::app, "Client disconnected");
		});

		server.set_message_handler([&server](connection_hdl hdl, websocket_server::message_ptr msg) {
			// Echo received message back to the client
			websocketpp::lib::error_code ec;
			server.send(hdl, msg->get_payload(), msg->get_opcode(), ec);
			if (ec) {
				server.get_alog().write(websocketpp::log::alevel::app, std::string("Send failed: ") + ec.message());
			}
		});

		server.listen(port);
		server.start_accept();

		std::cout << "WebSocket echo server listening on ws://0.0.0.0:" << port << std::endl;

		// Run ASIO in this thread but allow graceful stop
		while (!g_should_stop.load()) {
			server.poll();
			server.poll_one();
		}

		std::cout << "Shutting down..." << std::endl;
		server.stop_listening();
		server.stop();
	} catch (const std::exception& ex) {
		std::cerr << "Server exception: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}