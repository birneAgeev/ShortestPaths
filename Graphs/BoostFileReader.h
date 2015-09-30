#pragma once

#include<boost/iostreams/device/mapped_file.hpp>

#include "IFileReader.h"

class BoostFileReader : public IFileReader{
public:
	BoostFileReader();
	virtual ~BoostFileReader();

	void Open(const char* fileName);
	void Close();
	char NextChar();
	int NextInt();
	std::string ReadLine();
	bool IsEof();

private:
	boost::iostreams::mapped_file* memoryMappedFile;
	const char* fileData;
	const char* currentPosition;
	int size;
};