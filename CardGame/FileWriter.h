#pragma once
#include <fstream>
#include <iostream>
#define END_OF_FILE "0"

typedef const char* FILENAME;
typedef char byte;

//this class represents an object that can write to a file
class FileWriter {
public:

	FileWriter(FILENAME fileName);
	~FileWriter();

	//opens the file stream and is ready to write
	void Write();
	
	//write binary data into a file
	void writeData(byte* ptr, size_t size);

	//close the output stream after writing.
	void Close();
private:
	std::ofstream fs; //file stream to write to

	FILENAME fileName; //name of the file to write to

};

