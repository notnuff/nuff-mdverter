#include <iostream>
#include "FileOutput.h"

void FileOutput::open(const std::string &filePath) {
    _outputFile.open(filePath);
    std::cout << filePath;
    if(_outputFile.bad()){
        throw std::runtime_error("bad file path: " + filePath);
    }
}

FileOutput::~FileOutput() {
    _outputFile.close();
}

void FileOutput::write(const std::string &stringToWrite) {
    _outputFile << stringToWrite;
}

