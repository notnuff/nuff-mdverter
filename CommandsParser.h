//
// Created by notnuff on 02.03.24.
//

#ifndef NUFF_MDVERTER_COMMANDSPARSER_H
#define NUFF_MDVERTER_COMMANDSPARSER_H


#include <vector>
#include <string>
#include <stdexcept>

class CommandsParser {
private:
    bool _outFlag = false;
    bool _inFlag = false;
    std::string _outPath;
    std::string _inPath;
public:
    void parseCLI(int argc, char *argv[]);
    bool isOutFlag() const;
    const std::string &getOutPath();
    const std::string &getInPath();

};



#endif //NUFF_MDVERTER_COMMANDSPARSER_H
