#pragma once
#include "netCommon.h"

namespace net
{
	// This template allows us to validate the messages at compile time 
	template<typename T>
	struct msg_header
	{
		T id{}; //T represents Enum class
		uint32_t size = 0;
	};

	template<typename T>
	struct msg
	{
		msg_header<T> header{};
		std::vector<uint8_t> body;
		
		//returns the size of the msg in bytes
		size_t size() const
		{
			return sizeof(msg_header<T>) + body.size();
		}

		// override for std::cout compatibility for output to the console
		friend std::ostream& operator<< (std::ostream& os, const msg<T>& msg) 
		{
			os << "ID: " << int(msg.header.id) << " Size: " << msg.header.size;
		}

		// pushes data into the body vector
		template<typename K>
		friend msg<T>& operator<< (msg<T>& msg, const K& data)
		{
			// check if the data type K can be serialized
			static_assert(std::is_standard_layout<K>::value, "Data cannot be pushed into vector");

			// cache current size of the body vector
			size_t cache = msg.body.size();

			// resize the vector by the size of the data being pushed
			msg.body.resize(msg.body.size() + sizeof K);

			// copy the data to the allocated vector space
			std::memcpy(msg.body.data() + cache, &data, sizeof K);

			// update the size variable in the msg_header
			msg.header.size = msg.size();

			// return the target message
			return msg;
		}

		// extracting data from vector
		template<typename K>
		friend msg<T>& operator >> (msg<T>& msg, K& data)
		{
			// check if the data type K can be serialized
			static_assert(std::is_standard_layout<K>::value, "Data cannot be pushed into vector");

			// cache the location towards the end of the vector
			size_t cache = msg.body.size() - sizeof K;

			// copy the data from vector to the user variable
			std::memcpy(&data, msg.body.data() + cache, sizeof K);

			// reduce the size of the vector
			msg.body.resize(cache);

			// update the size variable in the msg_header
			msg.header.size = msg.size();

			// return the target message
			return msg;
		}
	};

	template<typename T>
	class connection;

	template<typename T>
	struct ownedMessage
	{
		std::shared_ptr<connection<T>> remote = nullptr;
		message<T> msg;

		// overload output stream operator
		friend std::ostream& operator<< (std::ostream& os, const ownedMessage<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
}