#include "ConnectionListener.h"

ConnectionListener::ConnectionListener(SharedContext& context) : context(context), b_listen(false), 
																	acceptor((*this->context), TCP::endpoint(TCP::v4(), 13))
{

}


ConnectionListener::ConnectionListener(const ConnectionListener& listener) : context(context), b_listen(true), 
																			 acceptor((*this->context), TCP::endpoint(TCP::v4(), 13))
{
	handleAccept();
}

void ConnectionListener::listen() {
	if (!b_listen) {
		b_listen = true;
		handleAccept();
	}
}

void ConnectionListener::mute() {
	b_listen = false;
}

ConnectionListener::ConnectQueue& ConnectionListener::getQueue() {
	return connectionQueue;
}

void ConnectionListener::handleAccept() {
	//if the listener is not supposed to listen, break the loop
	if (!b_listen) return;

	SharedSocket newSocket = std::make_shared<TCP::socket>((*context));

	acceptor.async_accept((*newSocket), [&newSocket, this](asio::error_code err) {
		if (!err) {
			//tell the client something went wrong;
			return;
		} else
			(*connectionQueue).post(newSocket);

		//an incomming connection is created and the shared socket instance is posted to the queue
	});

}

ConnectionListener::ConnectQueue ConnectionListener::connectionQueue = std::make_shared<ObjectProvider<SharedSocket>>();