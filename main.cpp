#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <regex>
#include "CommandsParser.h"
#include "IOfiles/OutputInterface.h"
#include "IOfiles/FileOutput.h"
#include "IOfiles/StandardTerminalOutput.h"



class TagEntry{
public:
    std::string::iterator beginOfTag;
    std::string::iterator endOfTag;
};


void checkBold(const std::string::iterator& it,
               const std::string& str,
               std::vector<TagEntry>& tagsStack){

    if (str.length() < 5) return;

    std::string checkStr{"**"};
    std::vector<char> restrictedSymbols{' ', '*'};

    auto local_it = it;

    for(auto checkChar : checkStr) {
        if (*local_it != checkChar) return;
        if (local_it == str.end()) return;
        local_it++;
    }

    auto replace_begin = it;
    auto replace_end = local_it;
    tagsStack.push_back({replace_begin, replace_end});

//    auto pre_replace = replace_begin;
//    auto post_replace = replace_end;
//
//    pre_replace--;
//    post_replace++;

//    if (replace_begin == str.begin()) {
//        for (auto restSym : restrictedSymbols){
//            if (*post_replace == restSym) return;
//        }
//        tagsStack.push_back({true, false, replace_begin, replace_end});
//        return;
//    }
//
//    if (replace_end == str.end()) {
//        for (auto restSym : restrictedSymbols){
//            if (*pre_replace == restSym) return;
//        }
//        tagsStack.push_back({false, true, replace_begin, replace_end});
//        return;
//    }
//
//    if (*pre_replace == ' ') {
//        for (auto restSym : restrictedSymbols){
//            if (*post_replace == restSym) return;
//        }
//        tagsStack.push_back({true, replace_begin, replace_end});
//    }
//
//    if (*post_replace == ' ') {
//        for (auto restSym : restrictedSymbols){
//            if (*pre_replace == restSym) return;
//        }
//        tagsStack.push_back({false, replace_begin, replace_end});
//    }
}

int main (int argc, char *argv[]) {
    CommandsParser cli;
    std::unique_ptr<OutputInterface> output;
    try {
        cli.parseCLI(argc, argv);
    }
    catch (const std::exception &err){
        std::cerr << err.what() << std::endl;
        std::cerr << "usage: nuff-mdverter <input> [--out|-o] <output> ...\n";
        return EXIT_FAILURE;
    }

    std::ifstream inputFile(cli.getInPath());
    if(inputFile.bad()) {
        std::cerr << "Input error: input file does not exists";
        return EXIT_FAILURE;
    }

    if (cli.isOutFlag()) {
        output = std::make_unique<FileOutput>();
        try{
            output->open(cli.getOutPath());
        } catch (std::exception &err) {
            std::cerr << "Output file error: ";
            std::cerr << &err;
            return EXIT_FAILURE;
        }
    }
    else {
        output = std::make_unique<StandardTerminalOutput>();
    }

    std::stringstream inputBuffer;
    std::stringstream outputBuffer;

    inputBuffer << inputFile.rdbuf();
    inputFile.close();

    std::string line;
    while(getline(inputBuffer, line)){
        static std::regex re(R"(_\S(.*?)\S_)");
        static std::string replacement = "<i>$1</i>";

        line = std::regex_replace(line, re, replacement);
        output->write(line);
    }
}

