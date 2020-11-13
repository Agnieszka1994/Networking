#pragma once

#include "netCommon.h"
#include "netTSQueue.h"
#include "netMessage.h"
#include "netConnection.h"

namespace net
{
	template<typename T>
	class ClientInterface
	{
	public:
		ClientInterface() : m_socket(m_context)
		{
			// associate the socket with the asio context
		}
		virtual ~ClientInterface()
		{
			disconnect();
		}
	public:
		// connect to the server with hostname, ip address and port
		bool connect(const std::string& host, const uint16_t port)
		{
			try
			{
				// create connection
				m_connection = std::make_unique<Connection<T>>();
				// TO DO.... 



				asio::ip::tcp::resolver resolver(m_context);
				// if it fails, it throws an exception
				m_endpoints = resolver.resolve(host, std::to_string(port));

				// tell the connection obj to connect to the server
				m_connection->connectToServer(m_endpoints);

				// start context thread
				thrContext = std::thread([this]() { m_context.run(); });

			}
			catch (std::exception& e)
			{
				std::cerr << "Client Exception: " << e.what() << std::endl;
				return false;
			}
			return false;
		}

		// disconnect from the server
		void disconnect()
		{
			// if the connceiton exists and it's connected:
			if (isConnected()) 
			{
				m_connection->disconnect();
			}
			// make sure that the asio context is running and stop it
			m_context.stop();
			if (thrContext.joinable())
			{
				thrContext.join();
			}

			// destroy the conncetion obj
			m_connection.release();

		}
		// check if a client is connected to the server
		bool isConnected() 
		{
			if (m_connection) 
			{
				return m_connection->isConnected();
			}
			else {
				return false;
			}	
		}

		TSQueue<ownedMessage<T>>& getIncoming()
		{
			return m_qMessagesIn;
		}
	protected:
		// handling data transfer
		asio::io_context m_context;
		std::thread thrContext;
		// hardware socket that is connected to the server
		asio::ip::tcp::socket m_socket;
		// each client has a unique instance of connection object
		std::unique_ptr<Connection<T>> m_connection;
	private:
		// queue of incoming messages from the server
		TSQueue<ownedMessage<T>> m_qMessagesIn;
	};
}