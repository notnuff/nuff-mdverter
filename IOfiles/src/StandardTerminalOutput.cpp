//
// Created by notnuff on 02.03.24.
//

#include "IOfiles/StandardTerminalOutput.h"

void StandardTerminalOutput::open(const std::string &somePathOrConsole) {

}

StandardTerminalOutput::~StandardTerminalOutput() {

}

void StandardTerminalOutput::write(const std::string &stringToWrite) {
    if (stringToWrite == "") std::cout << "\\n";
    std::cout << stringToWrite << "\n";
}
