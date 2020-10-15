#pragma once
#include <iostream>
#include <thread>
#include <string>

//this class reads from std::in.
class IOReader {
public:
	//constructor needs an identifier string, useful to keep several io threads apart
	IOReader(const std::string& identifier);
	IOReader(const IOReader&) = delete;
	IOReader(IOReader&& reader) noexcept;
	~IOReader();

	//starts the IOReader
	void start();

	//tells the IOReader to wait for a string from stdin
	void read();

	//retrieve what was written to the buffer. the entire buffer is moved to the new location and is emptied in this instance
	std::string&& getBuffer();

	//returns if IOReader is still listening to IO-input
	bool isReading() const;

	//Returns if IOReader is currently running
	bool isRunning() const;
	
	//shuts down IO reading
	void shutdown();

	//returns the identifier for this io stream
	std::string getIdentifier() const;

private:
	//the reading loop that waits for input
	void readingLoop();

	bool b_running; //ioreader should be running
	bool b_read; //ioreader should be awaiting input
	bool b_reading; //ioreader is waiting for input
	const std::string identifier; //identifier for this io thread
	
	std::string buffer; //buffer containing the read line

	std::thread iothread;
};

