#pragma once
#include <iostream>
#include <thread>
#include <string>

//this class reads from std::in.
class IOReader {
public:
	//constructor needs an identifier string, useful to keep several io threads apart
	IOReader(std::string&& identifier);
	IOReader() { }; //this standard constructor literally initializes no values and should not be used
	IOReader(const IOReader&) = delete;
	IOReader(IOReader&& reader) noexcept;
	~IOReader();

	IOReader& operator=(IOReader&& reader) noexcept;

	//starts the IOReader
	void start();

	//tells the IOReader to wait for a string from stdin
	void read();

	//retrieve what was written to the buffer. the entire buffer is moved to the new location and is emptied in this instance
	std::string&& getBuffer();

	//returns if IOReader is still listening to IO-input
	bool isReading() volatile const; //marking this function volatile tells the compiler that the value might change over time, making it safe to use in a while loop

	//Returns if IOReader is currently running
	bool isRunning() volatile const;
	
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
	std::string identifier; //identifier for this io thread
	
	std::string buffer; //buffer containing the read line

	std::thread iothread;
};

