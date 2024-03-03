//
// Created by notnuff on 02.03.24.
//

#ifndef NUFF_MDVERTER_FILEOUTPUT_H
#define NUFF_MDVERTER_FILEOUTPUT_H


#include <fstream>
#include "OutputInterface.h"

class FileOutput : public OutputInterface{
private:
    std::ofstream _outputFile;
public:
    void open(const std::string &filePath) override;
    void write (const std::string &stringToWrite) override;
    ~FileOutput() override;
};


#endif //NUFF_MDVERTER_FILEOUTPUT_H
