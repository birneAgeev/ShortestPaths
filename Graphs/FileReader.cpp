#define _CRT_SECURE_NO_WARNINGS

#include "FileReader.h"

FileReader::FileReader(){
    input = NULL;
    buffer = new char[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
}

FileReader::FileReader(FILE* input){
    this->input = input;
    memset(buffer, 0, BUFFER_SIZE);
}

FileReader::~FileReader(){
    Close();
    delete[] buffer;
	currentPosition = NULL;
}

void FileReader::Open(const char* fileName){
    input = fopen(fileName, "rt");
    
    if(input == NULL){
        std::cerr << "Error: can't open input file." << std::endl;
        exit(0);
    }

    fread(buffer, 1, BUFFER_SIZE, input);
    currentPosition = buffer;
}

void FileReader::Close(){
    fclose(input);
}

void FileReader::EnsureCapacity(){
    int residualSize = buffer + BUFFER_SIZE - currentPosition;
    if(residualSize < CRITCAL_CAPACITY){
        memcpy(buffer, currentPosition, residualSize);
        int readCount = fread(buffer + residualSize, 1, BUFFER_SIZE - residualSize, input);
		if (readCount < BUFFER_SIZE)
			buffer[readCount] = (char)0;
        currentPosition = buffer;
    }
}

bool FileReader::IsEof(){
	return *currentPosition == (char)0 && feof(input) != 0;
}

char FileReader::NextChar(){
    EnsureCapacity();
    while(*currentPosition <= ' ' && !IsEof())
        ++currentPosition;
    return *(currentPosition++);
}

int FileReader::NextInt() {
    EnsureCapacity();
	while (*currentPosition <= ' ' && !IsEof())
        ++currentPosition;
    bool sign = false;
    if(*currentPosition == '-') {
        sign = true;
        ++currentPosition;
    }
    int result = 0;
    while(*currentPosition > ' ')
        result = result * 10 + (*(currentPosition++) & 15);
    return sign ? -result : result;
}

std::string FileReader::ReadLine(){
    std::string result = "";

    EnsureCapacity();
    while(*currentPosition != '\r' && *currentPosition != '\n' && *currentPosition != 0){
        result += *currentPosition;
        ++currentPosition;
    }

    if(*currentPosition == '\r')
        currentPosition += 2;
    else
        ++currentPosition;

    return result;
}