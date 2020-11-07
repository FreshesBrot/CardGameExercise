#pragma once
#include <queue>

#include "../../Exceptions/EmptyQueueException.h"

//some typedefs for readability

//this class encapsulates a queue for handling messages
template<typename ProtocolType>
class ProtocolQueue {
	typedef std::queue<ProtocolType> Queue;
public:

	//intializes the queue
	ProtocolQueue() : b_available(false), queue(), size(0) { }

	//adds a protocol to the queue
	void post(ProtocolType protocol) {
		b_available = ++size;
		queue.push(protocol);
	}

	//retrieves first protocol in queue. throws an exception in case no protocols are available.
	ProtocolType fetch() {
		if (!size)
			throw EmptyQueueException();

		ProtocolType protocol = queue.front();
		queue.pop();
		b_available = --size;

		return protocol;

	}

	//asks the queue if there are any protocols available to be fetched
	bool available() const volatile {
		return b_available;
	}

	//returns the number of protocols in the queue
	size_t getSize() volatile {
		return size;
	}

	//some shortcut operators
	bool operator!() {
		return b_available;
	}

private:
	volatile bool b_available; //if any protocols are available atm

	Queue queue; //the internally managed queue
	volatile size_t size; // how many protocols are in this queue
};

