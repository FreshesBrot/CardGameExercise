#include "IOReader.h"
#define getl

IOReader::IOReader(std::string identifier) : b_running(false), b_read(false), b_reading(false), identifier(identifier) { }

IOReader::~IOReader() {
    shutdown();
    if(iothread.joinable())
        iothread.join();
}

void IOReader::start() {
    b_running = true;
    iothread = std::thread(&IOReader::readingLoop, this);
}

void IOReader::read() {
    b_read = true;
    b_reading = true;
}

std::string&& IOReader::getBuffer() {
    return std::move(buffer);
}

bool IOReader::isReading() const {
    return b_reading;
}

bool IOReader::isRunning() const {
    return b_running;
}

void IOReader::shutdown() {
    b_running = false;
}

void IOReader::readingLoop() {
    while (b_running) {
        if(!b_read) continue;
        
        b_read = false;
        std::cout << "waiting for input on " << identifier << "\r\n";

//two ways to read input
#ifdef getl
        std::getline(std::cin, buffer);
#else
        std::cin >> buffer;
#endif
       
        std::cout << "input received\n";

    b_reading = false;
    }
}
