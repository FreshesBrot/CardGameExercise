#pragma once
#include <string>
#include <vector>
#include <asio-1.18.0/include/asio.hpp>
#define KB 1024
#define MB 1024 * KB

using TCP = asio::ip::tcp;
typedef char byte_t;

//this class will manage connecting to the remote server for the first time
class ConnectionHandler {
public:

	//will start the connection handler and wait for it to connect
	ConnectionHandler(asio::io_context& context);

	//will stop the connection handler
	~ConnectionHandler();

	//will return 0 or 1 as a status code
	uint32_t connect(std::string& IP, std::string& port);

	//returns whether the connection handler is still receving data
	bool isReceiving() volatile const;

	//returns the buffer. this will clear the buffer and set curSize to 0!
	std::vector<byte_t>&& getBuffer();

	//returns the read size
	size_t getReadSize() const;

private:

	//static receiving buffer size that is used by the read handler to write into a temp buffer and then transfer it into the actual buffer
	inline static size_t tmpBufferSize = 1 * KB;
	//static buffer size for all instances
	inline static size_t bufferSize = 4 * KB;

	std::vector<byte_t> tmpBuffer;
	size_t curSize; //current size (location) of the last unwritten byte
	std::vector<byte_t> buffer; //the buffer the response will be loaded in. make sure buffer isnt overwritten
	

	asio::io_context& context; //the context this class will operate on
	TCP::socket connectSocket; //the socket that will handle the connection

	bool b_receiving; // a flag that determines if the connection is still receiving input
	//this function will handle reading the response from the server
	void readHandler();

};

