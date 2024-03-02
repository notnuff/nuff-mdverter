#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include "CommandsParser.h"
#include "OutputInterface.h"
#include "FileOutput.h"
#include "StandardTerminalOutput.h"

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

    std::string myText;
    while (getline(inputFile, myText)){
        output->write(myText);
    }
}