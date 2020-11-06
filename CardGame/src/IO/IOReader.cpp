#include "IOReader.h"
#define getl

IOReader::IOReader(std::string&& identifier) : b_running(false), b_read(false), b_reading(false), identifier(std::move(identifier)), buffer() { }

IOReader::IOReader(IOReader&& reader) noexcept : b_running(false), b_read(false), b_reading(false), identifier(), buffer() {
    *this = std::move(reader);
}

IOReader::~IOReader() {
    shutdown();
}

IOReader& IOReader::operator=(IOReader&& reader) noexcept {
    if (&reader == this) return *this;

    buffer.clear();
    b_running = false;
    b_read = false;
    b_reading = false;
    shutdown();

    buffer = std::move(reader.buffer);
    identifier = std::move(reader.identifier);

    if (reader.b_running) {
        reader.shutdown();
        start();
    }

    return *this;
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

bool IOReader::isReading() volatile const {
    return b_reading;
}

bool IOReader::isRunning() volatile const {
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
