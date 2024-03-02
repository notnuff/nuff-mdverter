//
// Created by notnuff on 02.03.24.
//

#ifndef NUFF_MDVERTER_STANDARDTERMINALOUTPUT_H
#define NUFF_MDVERTER_STANDARDTERMINALOUTPUT_H


#include <iostream>
#include "OutputInterface.h"

class StandardTerminalOutput : public OutputInterface{
private:

public:
    void open(const std::string &somePathOrConsole) override;
    void write (const std::string &stringToWrite) override;
    ~StandardTerminalOutput() override;
};


#endif //NUFF_MDVERTER_STANDARDTERMINALOUTPUT_H
