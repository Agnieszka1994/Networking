#pragma once
#include "netCommon.h"
// thread safe queue

namespace net 
{
	template<typename T>
	class TSQueue
	{
	protected:
		std::mutex muxQueue;
		std::deque<T> deqQueue;
	public:
		TSQueue() = default;
		TSQueue(const TSQueue<T>&) = delete; // not allow the queue to be copied
		virtual ~TSQueue() { clear(); }

		// returns and maintains item at front of Queue
		const T& front()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.front();
		}
		// returns and maintains item at back of Queue
		const T& back()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.back();
		}

		void push_back(cont T& item)
		{
			std::scoped_lock lock(muxQueue);
			deqQueue.emplace_back(std::move(item));
		}
		void push_front(cont T& item)
		{
			std::scoped_lock lock(muxQueue);
			deqQueue.emplace_front(std::move(item));
		}

		bool empty()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.empty();
		}

		size_t count() 
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.size();
		}
		// erases all of the items in the queue
		void clear()
		{
			std::scoped_lock lock(muxQueue);
			deqQueue.clear();
		}
		// removes and returns the item from front of Queue
		T pop_front() 
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.front());
			deqQueue.pop_front();
			return t;
		}

		// removes and returns the item from back of Queue
		T pop_back()
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.back());
			deqQueue.pop_back();
			return t;
		}

	};

}