#include "ConnectionListener.h"
#include <iostream>

ConnectionListener::ConnectionListener(SharedContext& connectContext, SharedContext& commsContext) :
	b_listen(false), connectContext(connectContext), acceptor((*connectContext), TCP::endpoint(TCP::v4(), 13)), commsContext(commsContext) {

}

void ConnectionListener::listen() {
	if (b_listen) return;
	
	b_listen = true;
	//start listening routine
	handleConnect();
}

void ConnectionListener::mute() {
	if (!b_listen) return;

	b_listen = false;
}

ConnectionListener::ConnectionQueue& ConnectionListener::getQueue() {
	return ConnectionListener::connections;
}

void ConnectionListener::handleConnect() {
	//if the listener is not supposed to listen, break the loop
	if (!b_listen) return;

	//socket for an endpoint to connect to
	SharedSocket socket = std::make_shared < TCP::socket>((*commsContext));
	try {

		acceptor.async_accept((*socket), [&socket, this](asio::error_code err) {
			if (!b_listen) {
				//tell the client the connection was denied
				/*(*socket).async_send(....);*/
				return;
			}

			//in case of error throw an error
			if (err)
				throw asio::system_error(err);

			//the tcp-socket in the SharedSocket is open once this function is called
			(*connections).post(socket);

			//continue loop
			handleConnect();
		});
	}
	catch (asio::system_error& err) {
		//if an error gets thrown, this might catch it, but not sure
		std::cout << "Error on Connection Attempt:\n" << err.what() << "\n";
		//restart handling connections
		handleConnect();
	}

}
