#include <iostream>
#include <net.h>

enum class CustomMsgTypes : uint32_t
{
	Fireball,
	MovePlayer
};

class CuctomClient : public net::ClientInterface<CustomMsgTypes>
{
public:
	// throw a fireball in a particular location
	bool Fireball(float x, float y)
	{
		// function creata a message and  send the data
		net::msg<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Fireball;
		msg << x << y;
		m_connection->sendMsg(msg);
	}
};

int main() {

	CuctomClient client;
	client.connect("community.onelonecoder.com", 60000);
	client.Fireball(2.0f, 5.0f);
	return 0;
}

//#include <iostream>
//#include <vector>
//#ifndef _WIN32
//#define _WIN32_WINNT 0x0A00
//#endif // !_WIN32
//#define ASIO_STANDALONE
//#include <asio.hpp>
//#include <asio/ts/buffer.hpp>
//#include <asio/ts/internet.hpp>
//
//std::vector<char> vBuffer(20 * 1024);
//void getData(asio::ip::tcp::socket& socket) {
//	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
//		[&](std::error_code ec, std::size_t length) {
//			if (!ec) {
//				std::cout << "\n\nRead " << length << " bytes\n\n";
//
//				for (int i = 0; i < length; i++)
//					std::cout << vBuffer[i];
//				getData(socket);
//			}
//		}
//	);
//}
//
//int main() {
//
//
//	asio::error_code ec;
//
//	// create a context - platform specific interface
//	asio::io_context context;
//
//	// create some fake tasks so the context does not finish
//	asio::io_context::work idleNetword(context);
//
//	// start the context on a separate thread
//	std::thread thrContext = std::thread([&]() { context.run(); });
//
//	// get the address of the endpoint
//	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);
//	// add a socket
//	asio::ip::tcp::socket socket(context);
//
//	// tell the socket to connect 
//	socket.connect(endpoint, ec);
//
//	if (!ec) {
//		std::cout << "Connected!" << std::endl;
//	}
//	else {
//		std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
//	}
//
//	if (socket.is_open()) {
//		getData(socket);
//		std::string sRequest =
//			"GET /index.html HTTP/1.1\r\n"
//			"Host: example.com\r\n"
//			"Connection: close\r\n\r\n";
//
//		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
//
//		using namespace std::chrono_literals;
//		std::this_thread::sleep_for(2000ms);
//
//		context.stop();
//		if (thrContext.joinable())
//			thrContext.join();
//	}
//}