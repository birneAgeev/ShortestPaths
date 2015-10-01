#pragma once

#include <cstdio>
#include <fstream>
#include <iostream>

#include "IFileReader.h"

class FileReader : public IFileReader {
public:
	FileReader();
	FileReader(FILE* input);
	virtual ~FileReader();

	void Open(const char* fileName) override;
	void Close() override;
	char NextChar() override;
	unsigned int NextUnsignedInt() override;
	std::string ReadLine() override;
	bool IsEof() override;

private:
	void EnsureCapacity();
	void SkipWhitespaces();

	FILE* input;
	static const int BUFFER_SIZE = 10000000;
	static const int CRITICAL_CAPACITY = 100;
	char* buffer;
	char* currentPosition;
};
