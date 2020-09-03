#include "FileReader.h"

FileReader::FileReader(FILENAME fileName) : fs() {
	this->fileName = fileName;
}

FileReader::~FileReader() {
	Close();
}

void
FileReader::Read() {
	if (!fs.is_open())
		fs.open(fileName, std::ios::in|std::ios::binary);
}

void FileReader::readBlock(byte* blockPtr, size_t blockSize) {
	fs.seekg(4, std::ios::beg); //stream has to start reading from 4th byte and up
	fs.read(blockPtr, blockSize);
}

size_t FileReader::getBlockSize() {
	size_t blockSize;
	fs.read((byte*)(void*)(&blockSize), 4); //first read deck size
	return blockSize;
}

void FileReader::Close() {
	if (fs.is_open())
		fs.close();
}
