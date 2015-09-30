#pragma once

#include <string>

class IFileReader{
public:
	virtual ~IFileReader() {}

	virtual void Open(const char* fileName) = 0;
	virtual void Close() = 0;
	virtual char NextChar() = 0;
	virtual int NextInt() = 0;
	virtual std::string ReadLine() = 0;
	virtual bool IsEof() = 0;
};