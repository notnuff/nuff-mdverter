cmake_minimum_required(VERSION 3.27)
project(nuff-mdverter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(nuff-mdverter
        main.cpp
        CommandsParser.cpp
        IOfiles/OutputInterface.h
        IOfiles/FileOutput.h
        IOfiles/src/FileOutput.cpp
        InputInterface.h
        IOfiles/StandardTerminalOutput.h
        IOfiles/src/StandardTerminalOutput.cpp)
