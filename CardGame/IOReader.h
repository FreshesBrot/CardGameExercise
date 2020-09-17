#pragma once
#include <iostream>
#include <thread>
#include <string>

//this class reads from std::in.
class IOReader {
public:
	//constructor needs an identifier string, useful to keep several io threads apart
	IOReader(std::string identifier);
	IOReader(const IOReader&) = delete;
	IOReader(IOReader&&) = delete;
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

	//the reading loop that waits for input
	void readingLoop();


private:
	bool b_running; //ioreader should be running
	bool b_read; //ioreader should be awaiting input
	bool b_reading; //ioreader is waiting for input
	std::string identifier; //identifier for this io thread
	
	std::string buffer; //buffer containing the read line

	std::thread iothread;
};
