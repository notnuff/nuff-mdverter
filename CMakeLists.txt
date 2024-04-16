cmake_minimum_required(VERSION 3.27)
project(nuff-mdverter)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(nuff-mdverter
        main.cpp
        CommandsParser.cpp
        IOfiles/OutputInterface.h
        IOfiles/FileOutput.h
        IOfiles/src/FileOutput.cpp
        IOfiles/InputInterface.h
        IOfiles/StandardTerminalOutput.h
        IOfiles/src/StandardTerminalOutput.cpp
        tokens/TokenInterface.h
        tokens/BoldToken.h
        tokens/BoldToken.cpp)
