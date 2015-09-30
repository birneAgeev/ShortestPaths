#include "BoostFileReader.h"

BoostFileReader::BoostFileReader(){
	memoryMappedFile = NULL;
	fileData = NULL;
	currentPosition = NULL;
	size = 0;
}

BoostFileReader::~BoostFileReader(){
	currentPosition = NULL;
	delete memoryMappedFile;
	delete[] fileData;
}

void BoostFileReader::Open(const char* fileName){
	memoryMappedFile = new boost::iostreams::mapped_file(fileName, boost::iostreams::mapped_file::readonly);
	fileData = memoryMappedFile->const_data();
	size = memoryMappedFile->size();
	currentPosition = fileData;
}

void BoostFileReader::Close(){
	memoryMappedFile->close();
	fileData = NULL;
	currentPosition = NULL;
	size = 0;
}

bool BoostFileReader::IsEof(){
	return currentPosition == fileData + size + 1;
}

char BoostFileReader::NextChar(){
	while (*currentPosition <= ' ' && !IsEof())
		++currentPosition;
	if (IsEof())
		return (char)0;
	return *(currentPosition++);
}

int BoostFileReader::NextInt() {
	while (*currentPosition <= ' ' && !IsEof())
		++currentPosition;
	bool sign = false;
	if (*currentPosition == '-') {
		sign = true;
		++currentPosition;
	}
	int result = 0;
	while (*currentPosition > ' ')
		result = result * 10 + (*(currentPosition++) & 15);
	return sign ? -result : result;
}

std::string BoostFileReader::ReadLine(){
	std::string result = "";

	while (*currentPosition != '\r' && *currentPosition != '\n' && *currentPosition != 0){
		result += *currentPosition;
		++currentPosition;
	}

	if (*currentPosition == '\r')
		currentPosition += 2;
	else
		++currentPosition;

	return result;
}