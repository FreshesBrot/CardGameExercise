#include "IOReader.h"
#define getl

IOReader::IOReader(const std::string& identifier) : b_running(false), b_read(false), b_reading(false), identifier(identifier), buffer() { }

IOReader::IOReader(IOReader&& reader) noexcept : b_running(false), b_read(false), b_reading(false), identifier(reader.identifier), buffer(std::move(reader.buffer)) {
    reader.shutdown();
}

IOReader::~IOReader() {
    shutdown();
}

void IOReader::start() {
    b_running = true;
    iothread = std::thread(&IOReader::readingLoop, this);
}

void IOReader::read() {
    if (!b_running)
        return;

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
    if (iothread.joinable())
        iothread.join();
}

void IOReader::readingLoop() {
    while (b_running) {
        if(!b_read) continue;
        
        b_read = false;
        //std::cout << "waiting for input on " << identifier << "\r\n";

//two ways to read input
#ifdef getl
        std::getline(std::cin, buffer);
#else
        std::cin >> buffer;
#endif
       
        //std::cout << "input received\n";

    b_reading = false;
    }
}

std::string IOReader::getIdentifier() const {
    return identifier;
}
