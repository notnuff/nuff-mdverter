//
// Created by notnuff on 02.03.24.
//

#ifndef NUFF_MDVERTER_OUTPUTINTERFACE_H
#define NUFF_MDVERTER_OUTPUTINTERFACE_H

#include <string>

class OutputInterface {
public:
    virtual void open(const std::string &somePathOrConsole) = 0;
    virtual void write(const std::string &stringToWrite) = 0;
    virtual ~OutputInterface() = default;
};

#endif //NUFF_MDVERTER_OUTPUTINTERFACE_H
