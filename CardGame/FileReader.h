#pragma once
#pragma once
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#define END_OF_FILE "0"

typedef char byte;

//this class represents an object that can read a file
class FileReader {
public:

	FileReader(const wchar_t* fileName);
	~FileReader();

	//opens the file stream for reading
	void Read();

	//reads blockSize bytes from the file and writes them to the block pointer. pointer should have the buffer size as specified from blockSize.
	void readBlock(byte* blockPtr, size_t blockSize);

	//returns how big the block (deck) will be
	size_t getBlockSize();

	//closes the file stream
	void Close();

private:

	//the file stream the class operates on
	std::ifstream fs;

	//name of the file
	std::wstring fileName;
	
};