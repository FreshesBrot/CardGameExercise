#pragma once
#include "ObjectProvider.h"
#include <memory>

//this class will subscribe to a queue and run a listener on a seperate thread. 
//classes that extend the subscriber class must provide the method "void listenHandler(ProtocolType)"
template<typename Object, typename Instance>
class Subscriber {
public:

	typedef std::shared_ptr<ObjectProvider<Object>> QueuePtr;

	//constructor that initializes a non-managed object along with an empty thread
	Subscriber(Instance* ptr) : queue(), b_keepListening(false), listenerThread(), p_instance(ptr) { };

	//destructor will make sure running thread is joined
	~Subscriber() {
			mute();
	}

	//will subscribe to a protocol provider and wait for messages
	void subscribe(QueuePtr& queue) {
		this->queue = queue;
	}

	//this will start a new thread that will listen in on the queue
	void listen() {
		if (b_keepListening) return;

		b_keepListening = true;
		listenerThread = std::thread([this]() { listenHandlerHead(); });
		
	}

	//this will shutdown the listener, destructing the thread, but keeping a ref to the queue
	void mute() {
		if (!b_keepListening) return;
		
		b_keepListening = false;
		if (listenerThread.joinable())
			listenerThread.join();
		
	}

private:
	QueuePtr queue; //the queue the subscriber will listen on
	
	bool b_keepListening; //flag that tells the listenHandler if it should keep listening

	std::thread listenerThread; //the thread the listener will run on

	//this function encapsulates listening on the subscribed queue
	void listenHandlerHead() {
		while (b_keepListening) {
			if (!(*queue)) continue;

			p_instance->listenHandler((*queue).fetch());

		}
	}

	//pointer to the an instance that implements the listenHandler function
	Instance* p_instance;

};