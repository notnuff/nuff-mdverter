

#include "CommandsParser.h"

void CommandsParser::parseCLI(int argc, char *argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    bool toWriteOut = false;
    if (argc <= 1) {
        throw std::runtime_error("Input error: no arguments were provided");
    }
    for (const auto &arg : args){
        if (arg == "--out" || arg == "-o") {
            if (_outFlag) {
                throw std::runtime_error("Input error: cannot use --out or -o twice");
            }
            toWriteOut = true;
            continue;
        }
        if (arg.at(0) == '-') {
            throw std::runtime_error("Unknown option: " + arg);
        }
        if (toWriteOut) {
            _outPath = arg;
            _outFlag = true;
            toWriteOut = false;
            continue;
        }
        if(_inFlag) {
            throw std::runtime_error("Input error: cannot input two input files at once");
        }
        _inPath = arg;
        _inFlag = true;
    }
    if (!_inFlag){
        throw std::runtime_error("Input error: no input provided");
    }
}

bool CommandsParser::isOutFlag() const {
    return _outFlag;
}

const std::string &CommandsParser::getOutPath() {
    return _outPath;
}

const std::string &CommandsParser::getInPath() {
    return _inPath;
}
