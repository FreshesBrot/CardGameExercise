#pragma once
#include <fstream>
#include <iostream>
#define END_OF_FILE "0"


//this class represents an object that can write to a file
class FileWriter {
public:

	FileWriter(const wchar_t* fileName);
	~FileWriter();

	//opens the file stream and is ready to write
	void Write();
	
	//write binary data into a file
	void writeData(char* ptr, size_t size);

	//close the output stream after writing.
	void Close();
private:
	std::ofstream fs; //file stream to write to

	std::wstring fileName; //name of the file to write to

};

