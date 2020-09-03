#include "FileWriter.h"

FileWriter::FileWriter(const wchar_t* fileName) {
	this->fileName = fileName;
}

FileWriter::~FileWriter() {
	Close();
}

void FileWriter::Write() {
	if (!fs.is_open())
		fs.open(fileName,std::ios::out,std::ios::binary);
}

void FileWriter::writeData(char* ptr, size_t size) {
	fs.write((char*)(void*)(&size), 4); //write 4 bytes integer for the file size
	fs.write(ptr, size); //then write card contents
}

void FileWriter::Close() {
	if (fs.is_open()) {
		fs.flush();
		fs.close();
	}
	
}
