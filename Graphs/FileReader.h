#pragma once

#include <cstdio>
#include <fstream>
#include <iostream>

#include "IFileReader.h"

class FileReader : public IFileReader{
public:
    FileReader();
    FileReader(FILE* input);
    virtual ~FileReader();

    void Open(const char* fileName);
    void Close();
    char NextChar();
    int NextInt();
    std::string ReadLine();
    bool IsEof();

private:
    void EnsureCapacity();

    FILE* input;
    static const int BUFFER_SIZE = 1000000;
    const int CRITCAL_CAPACITY = 100;
    char* buffer;
    char* currentPosition;
};