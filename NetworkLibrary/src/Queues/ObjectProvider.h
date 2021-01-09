#pragma once
#include <mutex>
#include <shared_mutex>

#include "ObjectQueue.h"

//macro that shortcuts acquiring a unique_lock
#define LOCK std::unique_lock<std::shared_mutex> lock(mutex)


//this class provides object queues as well as (threadsafe) access to them
template<typename Object>
class ObjectProvider {
public:

	ObjectProvider() : futureAccesses(0), mutex(), queue() { };

	//accesses the protocol queue to fetch first element in queue or the element in reserve. exception from queue.fetch() is passed up the call stack
	Object fetch() {
		LOCK;

		futureAccesses--;

		return queue.fetch();
	}

	void post(Object protocol) {
		LOCK;

		queue.post(protocol);
	}

	//whether any protocols are available in the queue.
	//since calling available means fetching an element right after, the queue keeps track of how many threads will access fetch immediately after,
	//returning false if too many threads would access the queue
	bool available() {
		LOCK;

		if (queue.available() && queue.getSize() > futureAccesses) {
			futureAccesses++;
			return true;
		} else return false;
	}

	//returns the number of protocols in this queue. since this member doesnt change any values, read access is thread safe and needs no lock
	size_t getSize() volatile const {
		return queue.getSize();
	}

	//clears the entire queue
	void clear() {
		LOCK;

		queue.clear();
	}

	//some operators that might shortcut some stuff
#pragma region Operator Overloads
	//shortcut for fetch()
	Object operator--(int) {
		return fetch();
	}

	//shortcut for post()
	void operator+(Object& object) {
		post(object);
	}

	//shortcut for post(protocol)
	void operator+=(Object protocol) {
		post(protocol);
	}

	//shortcut for available
	bool operator()() {
		return available();
	}

	//shortcut for !available()
	bool operator!() {
		return !available();
	}
#pragma endregion

private:
	uint32_t futureAccesses; //int that keeps track of how many threads will access the queue in the future

	std::shared_mutex mutex; //mutex to control access to the queue

	ObjectQueue<Object> queue; //internally managed queue

};

