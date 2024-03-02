//
// Created by notnuff on 02.03.24.
//

#include "StandardTerminalOutput.h"

void StandardTerminalOutput::open(const std::string &somePathOrConsole) {

}

StandardTerminalOutput::~StandardTerminalOutput() {

}

void StandardTerminalOutput::write(const std::string &stringToWrite) {
    std::cout << stringToWrite << '\n';
}
