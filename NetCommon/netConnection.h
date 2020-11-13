#pragma once

#include "netCommon.h"
#include "netTSQueue.h"
#include "netMessage.h"

namespace net
{
	template<typename T> // this allows the creation of shared pointers from within this object
	class Connection : public std::enable_shared_from_this<connection<T>>
	{
	public:
		Connection()
		{

		}
		virtual ~Connection()
		{

		}

	public:
		// can be called only by client
		bool connectToServer();
		// can be called by both client and server
		bool disconnect();
		bool isConnected() const;

		bool sendMsg(const msg<T>& msg);

	protected:
		// each connection has a unique socket
		asio::ip::tcp::socket m_socket;
		// this context is shared with the whole asio instance
		asio::io_context& m_asioContext;

		// this TSqueue holds all the messages to be sent to the remote side of the connection
		TSQueue<msg<T>> m_qMessagesOut;

		// this TSqueue holds all the messages that have been received
		// this is the reference as the remote side is expected to provide a queue
		TSQueue<ownedMessage>& m_qMessagesIn;
	};	

}