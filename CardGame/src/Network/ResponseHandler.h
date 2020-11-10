#pragma once
#include <memory>
#include <asio-1.18.0/include/asio.hpp>
#include "../Exceptions/NoConnectionException.h"

#define KB 1024

using TCP = asio::ip::tcp;
typedef std::shared_ptr<TCP::socket> SharedSocket;

//this class is responsible for handling incomming responses from the server
//this class is not copyable or moveable
class ResponseHandler {
public:
	//shorthand typedef for this class
	typedef std::vector<char> Buffer;

	//default constructor that doesnt initialize any values. puts the response handler in an invalid state
	ResponseHandler() : b_listen(false), socket(), buffer(), tmpBuffer(), curSize(0), b_valid(false) { };

	//constructor to initialize the response handler with the shared socket
	ResponseHandler(SharedSocket& socket);

	//destructor - not responsible for destructing the open socket!
	~ResponseHandler();

	//make the response handler listen async to incoming responses from the server.
	//this will throw an exception if the internal socket is not open, or the handler is invalid. in case
	//an exception is thrown, it will set the handler invalid either way
	void listen();

	//make the response handler stop listening for responses. sets the handler invalid, as the socket reference might be dead (i.e. closed)
	void mute();

	//whether this response handler is currently listening for responses
	bool isListening() const volatile;

	//checks if this response handler is valid and usable. an invalid handler should not be used.
	bool isValid() const;

	//returns the current buffer of the response listener. the buffer is cleared after calling this function.
	Buffer getBuffer();

	//this operator is used to initiate the response handler from an rvalue reference
	void operator()(ResponseHandler&& handler);

private:

	bool b_listen; //flag that tells the response handler to keep listening for responses

	SharedSocket socket; //shared socket to handle incomming connections

	Buffer buffer; //buffer that will hold the entire servers response
	Buffer tmpBuffer; //buffer that will hold incoming responses
	size_t curSize; //current (written) size of the buffer

	inline static uint32_t bufferSize = 4 * KB; //the total size of the buffer holding the response information
	inline static uint32_t tmpBufSize = 1 * KB; //the total size of the temporary buffer holding parts of the response information

	//this function is responsible for buffering incomming requests
	void readHandler();

	bool b_valid; //flag that checks if the response handler is currently in a valid state. is only unvalid if disconnected or default constructed

	ResponseHandler(const ResponseHandler&) = delete;
	//moving is permitted privately
	ResponseHandler(ResponseHandler&&);
	ResponseHandler& operator=(ResponseHandler&& handler);

};

